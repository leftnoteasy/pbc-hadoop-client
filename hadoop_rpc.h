#ifndef _HD_CLIENT_HADOOP_RPC_H
#define _HD_CLIENT_HADOOP_RPC_H

/* 
 * application id, it will be zero when we initialize,
 * and by current design, there will be only one app in each client
 */
extern int app_id;
extern int app_attempt_id;

typedef enum { 
    NM, // Node Mgr
    RM, // Resource Mgr
    NN, // NameNode, not used now
    DN  // DataNode, not used now
} hadoop_server_type_t;

typedef enum {
    CLIENT, // Client 
    AM      // App Master
} hadoop_client_type_t;

typedef struct {
    int caller_id;                     /* caller-id, assume user shouldn't access this */
    hadoop_client_type_t client_type;  /* client type */
    hadoop_server_type_t server_type;  /* server type */
    int socket_id;                     /* socket-id, assume user shouldn't access this */
    const char* protocol_name          /* name of protocol, assume user shouldn't access this */
} hadoop_rpc_proxy_t;

typedef struct {
} submit_application_context_t;

/**
 * get rpc proxy for user specified client/server type
 * return null when failed
 */ 
struct hadoop_rpc_proxy_t* new_hadoop_rpc_proxy(
    const char* host,
    int port,
    hadoop_client_type_t client_type, 
    hadoop_server_type_t server_type,
    const char* hadoop_version);       /* pass NULL we will use latest YARN version we support */

/**
 * submit application to YARN-RM
 * return 0 if succeed, otherwise, it's failed
 */
int submit_application(
    struct hadoop_rpc_proxy_t* proxy, 
    struct submit_application_context_t* context);

/**
 * init protobuf env, the pb_dir should contains compiled pb_file
 * return 0 if succeed, otherwise, it's failed
 */
int init_pb_env(const char* pb_dir, const char* hadoop_version);

/**
 * destory proxy
 */
void destory_hadoop_rpc_proxy(struct hadoop_rpc_proxy_t* proxy);

#endif