#include "hadoop_rpc.h"
#include "client_rm_protocol_impl.h"
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
#include <stdbool.h>
#include <string.h>

/* local variables */
bool is_env_initialize = false;
struct pbc_env* env;
const char* hadoop_version = NULL;

/******************
 * global methods *
 ******************/
hadoop_rpc_proxy_t* new_hadoop_rpc_proxy(
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
        printf("server cannot be null.\n");
        return NULL;
    }

    if ((server_type == NN) || (server_type == DN)) {
        printf("not support such server type now.\n");
        return NULL;
    }

    hadoop_rpc_proxy_t* proxy =
        (hadoop_rpc_proxy_t*)malloc(sizeof(hadoop_rpc_proxy_t));
    proxy->caller_id = 0;
    proxy->client_type = client_type;
    proxy->server_type = server_type;

    if (NM == proxy->server_type) {
        proxy->protocol_name = CONTAINER_MANAGER_PROTOCOL_NAME;
    } else if (RM == proxy->server_type) {
        if (CLIENT == proxy->client_type) {
            proxy->protocol_name = CLIENT_RM_PROTOCOL_NAME;
        } else if (AM == proxy->client_type) {
            proxy->protocol_name = AM_RM_PROTOCOL_NAME;
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
    rc = write_connection_header(proxy);
    if (rc != 0) {
        printf("write connection header failed.\n");
        return NULL;
    }

    // succeed created
    proxy->app_id = -1;
    return proxy;
}

int init_pb_env(const char* pb_dir, const char* hd_version) {
    env = pbc_new();

    if (is_env_initialize) {
        printf("env is already initialized.\n");
        return 0;
    }
    int pb_count = init_pbc_env_with_dir(pb_dir, env);
    if (pb_count <= 0) {
        printf("initialize pb env failed.\n");
        return 1;
    }
    
    // initialize succeed
    is_env_initialize = true;
    if (NULL != hd_version) {
        hadoop_version = strdup(hd_version);
    }
    return 0;
}

void destory_pb_env() {

}

/**
 * destory proxy
 */
void destory_hadoop_rpc_proxy(hadoop_rpc_proxy_t* proxy) {

}

int submit_application(
    hadoop_rpc_proxy_t* proxy, 
    submit_application_context_t* context) {
    int rc = get_new_app(proxy);
    if (rc != 0) {
        printf("get new application invoke failed.\n");
        return -1;
    }
    return 0;
}

/* static method implementation */

