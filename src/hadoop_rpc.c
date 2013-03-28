#include "hadoop_rpc.h"
#include "net_utils.h"
#include "pbc_utils.h"
#include "str_utils.h"
#include "hadoop_rpc_constants.h"

#include "ext/pbc/pbc.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

/* global variables */
int app_id = -1;
int app_attempt_id = 0;

/* local variables */
bool is_env_initialize = false;
struct pbc_env env;
const char* hadoop_version = NULL; 

/* static methods decleration */
static bool check_init_and_print();
static int connect_to_server(int socket_id, const char* host, int port);
static int write_all(int socket_id, const char* buffer, int size);
static int write_connection_header(struct hadoop_rpc_proxy_t* proxy);
static int generate_request_header(char** buffer, int* size);
static int generate_new_app_request(char** buffer, int* size);
static int generate_hadoop_request(const char* request, const char* protocol, 
    char** buffer, int* size);
static int write_request(
    int socket_id, 
    const char* header, 
    int header_len, 
    const char* request, 
    int request_len);

/* global methods */
struct hadoop_rpc_proxy_t* new_hadoop_rpc_proxy(
    const char* host,
    int port,
    hadoop_client_type_t client_type, 
    hadoop_server_type_t server_type) {
    int rc;

    // check initialize
    if (!check_init_and_print()) {
        return NULL;
    }

    // insanity check
    if (!host) {
        printf("server cannot be null");
        return NULL;
    }

    if ((server_type == NN) || (server_type == DN)) {
        printf("not support such server type now");
        return NULL;
    }

    struct hadoop_rpc_proxy_t* proxy =
        (struct hadoop_rpc_proxy_t*)malloc(struct hadoop_rpc_proxy_t);
    proxy->caller_id = 0;
    proxy->client_type = client_type;
    proxy->server_type = server_type;

    if (NM == proxy->server_type) {
        proxy->protocl_name = CONTAINER_MANAGER_PROTOCOL_NAME;
    } else if (RM == proxy->server_type) {
        if (CLIENT == proxy->client_type) {
            proxy->protocl_name = CLIENT_RM_PROTOCOL_NAME;
        } else if (AM == proxy->client_type) {
            proxy->protocl_name = AM_RM_PROTOCOL_NAME;
        }
    }

    // init socket for proxy, and connect to server
    proxy->socket_id = socket(AF_INET, SOCK_STREAM, 0);
    rc = connect_to_server(proxy->socket_id, host, port);

    if (rc != 0) {
        free(proxy);
        return NULL;
    }

    // write connection header to this socket
    rc = write_connection_header(socket_id);
    if (rc != 0) {
        printf("write connection header failed");
        return NULL;
    }

    // succeed created
    return proxy;
}

int init_pb_env(const char* pb_dir, const char* hd_version) {
    if (is_env_initialize) {
        printf("env is already initialized");
        return 0;
    }
    int pb_count = init_pbc_env_with_dir(pb_dir, &env);
    if (pb_count <= 0) {
        printf("initialize pb env failed");
        return 1;
    }
    
    // initialize succeed
    is_env_initialize = true;
    if (NULL != hd_version) {
        hadoop_version = strdup(hd_version);
    }
    return 0;
}

int submit_application(
    struct hadoop_rpc_proxy_t* proxy, 
    struct submit_application_context_t* context) {
    if (-1 != app_id) {
        printf("there's already a app, id=%d, will exit\n", app_id);
        return -1;
    }
}

/* static method implementation */

/* check if initialized pb-env and print error msg */
static bool check_init_and_print() {
    if (!is_env_initialize){
        printf("initialize pb_env before use this function");
        return false;
    }
    return true;
}

/* connect_to_server, return 0 if succeed */
static int connect_to_server(int socket_id, const char* host, int port) {
    //define socket variables
    struct sockaddr_in serv_addr;
    struct hostent *server;

    //init port / socket / server
    server = gethostbyname(host);
    if (server == NULL)
    {
        fprintf(stderr,"ERROR, no such host");
        return -1;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
                server->h_length);
                serv_addr.sin_port = htons(port);
                 
    //connect via socket
    if (connect(socket_id, &serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("ERROR connecting");
        return -1;
    }

    return 0;
}

/* write connection header to socket */
static int write_connection_header(struct hadoop_rpc_proxy_t* proxy) {
    int rc;
    struct pbc_slice slice;

    if (!proxy) {
        printf("proxy cannot be null");
        return -1;
    }

    /**
     * Write the connection header - this is sent when connection is established
     * +----------------------------------+
     * |  "hrpc" 4 bytes                  |      
     * +----------------------------------+
     * |  Version (1 bytes)               | (This should be 7 for 2.0.x)
     * +----------------------------------+
     * |  Authmethod (1 byte)             | (80->SIMPLE), (81->GSSAPI), (82-DIGEST)
     * +----------------------------------+
     * |  IpcSerializationType (1 byte)   | (should be 0)
     * +----------------------------------+
     */
    rc = write_all(proxy->socket_id, "hrpc", 4);
    if (rc != 0) {
        printf("write hrpc failed");
        return -1;
    }

    char v = 7;
    rc = write_all(proxy->socket_id, &v, 1);
    if (rc != 0) {
        printf("write version failed");
        return -1;
    }

    v = 80;
    rc = write_all(proxy->socket_id, &v, 1);
    if (rc != 0) {
        printf("write auth method failed");
        return -1;
    }

    v = 0;
    rc = write_all(proxy->socket_id, &v, 1);
    if (rc != 0) {
        printf("write serialization type failed");
        return -1;
    }

    /* write IpcConectionContextProto to socket */
    struct pbc_wmessage* ipc_proto = pbc_wmessage_new(&env, 
        "hadoop.common.IpcConnectionContextProto");
    pbc_wmessage_string(ipc_proto, "protocol", proxy->protocl_name, -1);
    pbc_wmessage_buffer(ipc_proto, &slice);

    /* write length of IpcConnectionContextProto */
    int len = int_endian_swap(slice.len)
    rc = write_all((char*)len, 4);
    if (rc != 0) {
        printf("write length of ipc connection context failed");
        pbc_wmessage_delete(ipc_proto);
        free(slice.buffer);
        return -1;
    }

    /* write content of pack context */
    rc = write_all((char*)slice.buffer, slice.len);
    if (rc != 0) {
        printf("write IpcConectionContextProto failed");
        pbc_wmessage_delete(ipc_proto);
        free(slice.buffer);
        return -1;
    }

    pbc_wmessage_delete(ipc_proto);
    free(slice.buffer);

    return -1;
}

/* try to write all buffer to socket incase not all data written
 * will failed when write failed
 */
static int write_all(int socket_id, const char* buffer, int size) {
    int bytes_written = 0;
    int retval;

    // we will not do anything for null buffer
    if (!buffer) {
        printf("buffer is null, will return");
        return 0;
    }

    while (bytes_written < size) {
        retval = write(socket_id, buffer + bytes_written, size - bytes_written);
        if (retval >= 0){
            bytes_written += retval;
        } else {
            printf("error in writting data");
            return -1;
        }
    }

    return 0;
}

/* try to write request to socket
 * -----------------------------------------------
 * | length of length(header) + length(request)  |
 * | header = raw_varint_int(header) + header    |
 * | request = raw_varint_int(request) + request |
 * -----------------------------------------------
 */
static int write_request(
    int socket_id, 
    const char* header, 
    int header_len, 
    const char* request, 
    int request_len) {
    const MAX_VINT_SIZE = 8;

    char header_len_buffer[MAX_VINT_SIZE];
    char request_len_buffer[MAX_VINT_SIZE];
    int rc;

    int header_vint_len = write_raw_varint32(&(header_len_buffer[0]), header_len);
    int request_vint_len = write_raw_varint32(&(request_len_buffer[0]), request_len);

    /* write total length */
    int total_len = int_endian_swap(header_vint_len + header_len + request_vint_len + request_len);
    rc = write_all(socket_id, (char*)(&total_len), 4);
    if (0 != rc) {
        printf("write total length failed.");
        return -1;
    }

    /* write of header vint */
    rc = write_all(socket_id, header_len_buffer, header_vint_len);
    if (0 != rc) {
        printf("write header vint failed.");
        return -1;
    }

    /* write header */
    rc = write_all(socket_id, header, header_len);
    if (0 != rc) {
        printf("write header buffer failed.");
        return -1;
    }

    /* write of request vint */
    rc = write_all(socket_id, request_len_buffer, request_vint_len);
    if (0 != rc) {
        printf("write request vint failed.");
        return -1;
    }

    /* write header */
    rc = write_all(socket_id, request, request_len);
    if (0 != rc) {
        printf("write request buffer failed.");
        return -1;
    }

    return 0;
}

/* generate header for request :
    enum RpcKindProto {
      RPC_BUILTIN          = 0;  // Used for built in calls by tests
      RPC_WRITABLE         = 1;  // Use WritableRpcEngine 
      RPC_PROTOCOL_BUFFER  = 2;  // Use ProtobufRpcEngine
    }
     
    enum RpcPayloadOperationProto {
      RPC_FINAL_PAYLOAD        = 0; // The final payload
      RPC_CONTINUATION_PAYLOAD = 1; // not implemented yet
      RPC_CLOSE_CONNECTION     = 2; // close the rpc connection
    }
        
    message RpcPayloadHeaderProto { // the header for the RpcRequest
      optional RpcKindProto rpcKind = 1;
      optional RpcPayloadOperationProto rpcOp = 2;
      required uint32 callId = 3; // each rpc has a callId that is also used in response
    }
*/
static int generate_request_header(char** buffer, int* size, int caller_id) {

}

/* 
message HadoopRpcRequestProto {
  required string methodName = 1; 
  optional bytes request = 2;
  required string declaringClassProtocolName = 3;
  required uint64 clientProtocolVersion = 4;
}
 
 * An example,
 * methodName: "getAllApplications"
 * request: GetAllApplicationRequest.getBytes()
 * declaringClassProtocolName: "org.apache.hadoop.yarn.api.ClientRMProtocolPB"
 * clientProtocolVersion: 1
*/
static int generate_hadoop_request(const char* request, const char* protocol, 
    char** buffer, int* size) {

}

/* ClientRMProtocol.getNewApplication */
static int generate_new_app_request(char** buffer, int* size) {

}

