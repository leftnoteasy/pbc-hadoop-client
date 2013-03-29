#ifndef _HD_CLIENT_HADOOP_RPC_H
#define _HD_CLIENT_HADOOP_RPC_H

#include <stdbool.h>

extern struct pbc_env* env;
extern bool is_env_initialize;

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
    const char* protocol_name;         /* name of protocol, assume user shouldn't access this */
    int app_id;                        /* application-id */
    int app_attempt_id;                /* application-attempt-id */
    long cluster_timestamp;            /* time stamp of the cluster */
} hadoop_rpc_proxy_t;

typedef struct {
} submit_application_context_t;

/**
 * get rpc proxy for user specified client/server type
 * return null when failed
 */ 
hadoop_rpc_proxy_t* new_hadoop_rpc_proxy(
    const char* host,
    int port,
    hadoop_client_type_t client_type, 
    hadoop_server_type_t server_type);       /* pass NULL we will use latest YARN version we support */

/**
 * submit application to YARN-RM
 * return 0 if succeed, otherwise, it's failed
 */
int submit_application(
    hadoop_rpc_proxy_t* proxy, 
    submit_application_context_t* context);

/**
 * init protobuf env, the pb_dir should contains compiled pb_file
 * return 0 if succeed, otherwise, it's failed
 */
int init_pb_env(const char* pb_dir, const char* hadoop_version);

/**
 * destory pb environment 
 */
void destory_pb_env();

/**
 * destory proxy
 */
void destory_hadoop_rpc_proxy(hadoop_rpc_proxy_t* proxy);

#endif