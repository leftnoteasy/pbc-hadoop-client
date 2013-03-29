#include "hadoop_rpc.h"
#include "net_utils.h"
#include "pbc_utils.h"
#include "str_utils.h"
#include "hadoop_rpc_constants.h"
#include "hadoop_rpc_utils.h"

#include "ext/pbc/pbc.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <string.h>

/* check if initialized pb-env and print error msg */
bool check_init_and_print() {
    if (!is_env_initialize){
        printf("initialize pb_env before use this function.\n");
        return false;
    }
    return true;
}

/* connect_to_server, return 0 if succeed */
int connect_to_server(int socket_id, const char* host, int port) {
    //define socket variables
    struct sockaddr_in serv_addr;
    struct hostent *server;

    //init port / socket / server
    server = gethostbyname(host);
    if (server == NULL)
    {
        fprintf(stderr,"ERROR, no such host.\n");
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
        printf("ERROR connecting.\n");
        return -1;
    }

    return 0;
}

/* write connection header to socket */
int write_connection_header(hadoop_rpc_proxy_t* proxy) {
    int rc;
    struct pbc_slice slice;

    if (!proxy) {
        printf("proxy cannot be null.\n");
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
        printf("write hrpc failed.\n");
        return -1;
    }

    char v = 7;
    rc = write_all(proxy->socket_id, &v, 1);
    if (rc != 0) {
        printf("write version failed.\n");
        return -1;
    }

    v = 80;
    rc = write_all(proxy->socket_id, &v, 1);
    if (rc != 0) {
        printf("write auth method failed.\n");
        return -1;
    }

    v = 0;
    rc = write_all(proxy->socket_id, &v, 1);
    if (rc != 0) {
        printf("write serialization type failed.\n");
        return -1;
    }

    /* write IpcConectionContextProto to socket */
    struct pbc_wmessage* ipc_proto = pbc_wmessage_new(env, 
        "hadoop.common.IpcConnectionContextProto");
    pbc_wmessage_string(ipc_proto, "protocol", proxy->protocol_name, 0);
    pbc_wmessage_buffer(ipc_proto, &slice);

    /* write length of IpcConnectionContextProto */
    int len = int_endian_swap(slice.len);
    rc = write_all(proxy->socket_id, (char*)(&len), 4);
    if (rc != 0) {
        printf("write length of ipc connection context failed.\n");
        pbc_wmessage_delete(ipc_proto);
        return -1;
    }

    /* write content of pack context */
    rc = write_all(proxy->socket_id, (char*)(slice.buffer), slice.len);
    if (rc != 0) {
        printf("write IpcConectionContextProto failed.\n");
        pbc_wmessage_delete(ipc_proto);
        free(slice.buffer);
        return -1;
    }

    pbc_wmessage_delete(ipc_proto);

    return 0;
}

/* try to write request to socket
 * -----------------------------------------------
 * | length of length(header) + length(request)  |
 * | header = raw_varint_int(header) + header    |
 * | request = raw_varint_int(request) + request |
 * -----------------------------------------------
 */
int write_request(
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
        printf("write total length failed.\n");
        return -1;
    }

    /* write of header vint */
    rc = write_all(socket_id, header_len_buffer, header_vint_len);
    if (0 != rc) {
        printf("write header vint failed.\n");
        return -1;
    }

    /* write header */
    rc = write_all(socket_id, header, header_len);
    if (0 != rc) {
        printf("write header buffer failed.\n");
        return -1;
    }

    /* write of request vint */
    rc = write_all(socket_id, request_len_buffer, request_vint_len);
    if (0 != rc) {
        printf("write request vint failed.\n");
        return -1;
    }

    /* write header */
    rc = write_all(socket_id, request, request_len);
    if (0 != rc) {
        printf("write request buffer failed.\n");
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
int generate_request_header(char** p_buffer, int* size, int caller_id) {
    struct pbc_wmessage* header = pbc_wmessage_new(env, 
        "hadoop.common.RpcPayloadHeaderProto");
    struct pbc_slice slice;

    pbc_wmessage_integer(header, "rpcKind", 2, 0);
    pbc_wmessage_integer(header, "rpcOp", 0, 0);
    pbc_wmessage_integer(header, "callId", caller_id, 0);

    pbc_wmessage_buffer(header, &slice);
    *p_buffer = (char*)malloc(slice.len);
    memcpy(*p_buffer, slice.buffer, slice.len);
    *size = slice.len;

    pbc_wmessage_delete(header);
    return 0;
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
int generate_hadoop_request(const char* request, 
    int request_len, 
    const char* protocol, 
    const char* method,
    char** pbuffer, 
    int* size) {
    struct pbc_wmessage* rmsg = pbc_wmessage_new(env, "hadoop.common.HadoopRpcRequestProto");
    struct pbc_slice slice;

    pbc_wmessage_string(rmsg, "methodName", method, 0);
    pbc_wmessage_string(rmsg, "request", request, request_len);
    pbc_wmessage_string(rmsg, "declaringClassProtocolName", protocol, 0);
    pbc_wmessage_integer(rmsg, "clientProtocolVersion", 1, 0);

    pbc_wmessage_buffer(rmsg, &slice);
    *pbuffer = (char*)malloc(slice.len);
    memcpy(*pbuffer, slice.buffer, slice.len);
    *size = slice.len;
    pbc_wmessage_delete(rmsg);

    return 0;
}


/* read header of response, it will first read a varint32 of header size, 
 * then following is header
 * if SUCCEED, (return RESPONSE_SUCCEED), it will also read response buffer and size
 * if ERROR, (return RESPONSE_ERROR), then you can call read_exception(...) to get 
 *    what happended
 * if FATAL, (return RESPONSE_FATAL), then you can call read_fatal to get version of
 *    server side
 */ 
response_type_t recv_rpc_response(hadoop_rpc_proxy_t* proxy,
    char** response, int* size) {

    int read_count;
    int rc;
    struct pbc_slice slice;
    
    /* read length of header */
    rc = read_raw_varint32(proxy->socket_id, &read_count, &(slice.len));
    if ((rc != 0) || (slice.len <= 0)) {
        printf("read response header length failed.\n");
        return RESPONSE_OTHER_ERROR;
    }

    slice.buffer = malloc(slice.len);
    if (!(slice.buffer)) {
        printf("Out of memory when alloc.\n");
        return RESPONSE_OTHER_ERROR;
    }

    /* read header buffer from socket */
    rc = read_all(proxy->socket_id, (char*)(slice.buffer), slice.len);
    if (rc != 0) {
        printf("read head buffer from socket failed.\n");
        free(slice.buffer);
        return RESPONSE_OTHER_ERROR;
    }

    /* de-serialize header from buffer */
    struct pbc_rmessage* m = pbc_rmessage_new(env, "hadoop.common.RpcResponseHeaderProto", &slice);
    if (!m) {
        printf("Error : %s, \n", pbc_error(env));
        free(slice.buffer);
        return RESPONSE_OTHER_ERROR;
    }

    /* get type of response */
    int response_status = pbc_rmessage_integer(m, "status", 0, NULL);
    int response_caller_id = pbc_rmessage_integer(m, "callId", 0, NULL);
    int response_server_ipc_version = pbc_rmessage_integer(m, "serverIpcVersionNum", 0, NULL);

    /* now we can delete the header message now */
    pbc_rmessage_delete(m);

    /* check caller-id if equals to previous id in proxy, if not, something wrong */
    if (response_caller_id != proxy->caller_id - 1) {
        printf("caller-id not match, %d:%d.\n", response_caller_id, proxy->caller_id - 1);
        return RESPONSE_OTHER_ERROR;
    }

    /* check type */
    if (response_status == 0) {
        // SUCCESS, read response buffer out and return
        int response_size;
        read(proxy->socket_id, &response_size, 4);
        // transfer it to c-syle
        response_size = int_endian_swap(response_size);
        if (response_size <= 0) {
            printf("something wrong in reading size of response payload length.\n");
            return RESPONSE_OTHER_ERROR;
        }
        // create response buffer and read them out
        *response = (char*)malloc(response_size);
        if (!(*response)) {
            printf("out of memory when read response.\n");
            return RESPONSE_OTHER_ERROR;
        }
        rc = read_all(proxy->socket_id, *response, response_size);
        if (rc != 0) {
            printf("error in read response payload content.\n");
            free(*response);
            return RESPONSE_OTHER_ERROR;
        }
        // set read length of response payload
        *size = response_size;
        return RESPONSE_SUCCEED;
    } else if (response_status == 1) {
        return RESPONSE_ERROR;
    } else {
        printf("FATAL error of response, version not match, server version is:%d\n", 
            response_server_ipc_version);
        return RESPONSE_FATAL;
    }
}

/* send the whole rpc payload to socket, will add header for it */
int send_rpc_request(hadoop_rpc_proxy_t* proxy, char* request_payload, int request_payload_len) {
    int rc;

    char* header = NULL;
    char* request = NULL;
    int header_len;
    int request_len;

    // generate header for hadoop_request
    rc = generate_request_header(&header, &header_len, proxy->caller_id);
    if (0 != rc) {
        printf("generate request header failed.\n");
    }

    // now, write header and request to socket
    rc = write_request(proxy->socket_id, header, header_len, request_payload, request_payload_len);
    if (0 != rc) {
        printf("write request payload to socket failed.\n");
        free(header);
        return -1;
    }
    free(header);

    // increase caller_id, wait for response
    proxy->caller_id++;

    return 0;
}

/* read error, return 0 if SUCCEED, and put error msg to params */
int read_exception(hadoop_rpc_proxy_t* proxy, 
    char** exception_class, 
    char** exception_stack) {
    int len;
    int rc;

    /* read exception_class */
    rc = read_all(proxy->socket_id, &len, 4);
    if (0 != rc) {
        printf("read length of exception failed.\n");
        return -1;
    }
    len = int_endian_swap(len);
    *exception_class = (char*)malloc(len + 1);
    if (!(*exception_class)) {
        printf("OOM when allocate exception class.\n");
        return -1;
    }
    rc = read_all(proxy->socket_id, *exception_class, len);
    if (0 != rc) {
        printf("read exception class string failed.\n");
        free(*exception_class);
        return -1;
    }
    (*exception_class)[len] = '\0';

    /* read exception_stack */
    rc = read_all(proxy->socket_id, &len, 4);
    if (0 != rc) {
        printf("read length of exception failed.\n");
        return -1;
    }
    len = int_endian_swap(len);
    *exception_stack = (char*)malloc(len + 1);
    if (!(*exception_stack)) {
        printf("OOM when allocate exception stack.\n");
        return -1;
    }
    rc = read_all(proxy->socket_id, *exception_stack, len);
    if (0 != rc) {
        printf("read exception class string failed.\n");
        free(*exception_stack);
        return -1;
    }
    (*exception_stack)[len] = '\0';

    // SUCCEED
    return 0;
}

void process_bad_rpc_response(hadoop_rpc_proxy_t* proxy, response_type_t type) {
    int rc;
    if (RESPONSE_ERROR == type) {
        char* exception_class = NULL;
        char* exception_stack = NULL;
        rc = read_exception(proxy, &exception_class, &exception_stack);
        if (0 != rc) {
            printf("read error of response failed.\n");
            return;
        }
        printf("error of response, class:%s\nstack_trace:%s\n.", exception_class, exception_stack);
        return;
    } else {
        printf("some other error caused failed.\n");
        return;
    }
}