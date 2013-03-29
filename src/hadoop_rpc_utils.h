#ifndef _HD_CLIENT_HADOOP_RPC_UTILS_H_
#define _HD_CLIENT_HADOOP_RPC_UTILS_H_

#include "hadoop_rpc.h"
#include <stdbool.h>

/* type of RPC PB response */
typedef enum {
    RESPONSE_SUCCEED,
    RESPONSE_ERROR,
    RESPONSE_FATAL,
    RESPONSE_OTHER_ERROR
} response_type_t;

/* check if initialized pb-env and print error msg */
bool check_init_and_print();

/* connect_to_server, return 0 if succeed */
int connect_to_server(int socket_id, const char* host, int port);

/* write connection header to socket */
int write_connection_header(hadoop_rpc_proxy_t* proxy);

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
int generate_request_header(char** buffer, int* size, int caller_id);

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
    char** buffer, 
    int* size);

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
    int request_len);

/* read response, it will first read a varint32 of header size, 
 * then following is header
 * if SUCCEED, (return RESPONSE_SUCCEED), it will also read response buffer and size
 * if ERROR, (return RESPONSE_ERROR), then you can call read_exception(...) to get 
 *    what happended
 * if FATAL, (return RESPONSE_FATAL), then you can call read_fatal to get version of
 *    server side
 */ 
response_type_t recv_rpc_response(hadoop_rpc_proxy_t* proxy,
    char** response, int* size);

/* read error, return 0 if SUCCEED, and put error msg to params */
int read_exception(hadoop_rpc_proxy_t* proxy, 
    char** exception_class, 
    char** exception_stack);

/* send the whole rpc payload to socket, will add header for it */
int send_rpc_request(hadoop_rpc_proxy_t* proxy, 
    char* request_payload, 
    int request_payload_len);

#endif //_HD_CLIENT_HADOOP_RPC_UTILS_H_