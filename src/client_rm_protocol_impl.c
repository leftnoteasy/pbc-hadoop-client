#include "client_rm_protocol_impl.h"
#include "hadoop_rpc_utils.h"
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
#include <stdbool.h>
#include <string.h>

/* static methods*/
static int generate_new_app_request(char** buffer, int* size);

/* global methods */
int get_new_app(hadoop_rpc_proxy_t* proxy) {
    int rc;
    if (-1 != proxy->app_id) {
        printf("there's already a app, id=%d, will exit\n", proxy->app_id);
        return -1;
    }

    char* request = NULL;
    int request_len;

    /*****************************************************
     * first, we will submit CreateNewApplicationRequest *
     *****************************************************/

    // generate new_application_request
    rc = generate_new_app_request(&request, &request_len);
    if (0 != rc) {
        printf("generate new app request failed.\n");
        return -1;
    }

    // send request
    rc = send_rpc_request(proxy, request, request_len);
    if (0 != rc) {
        printf("send new_application_request failed.\n");
        free(request);
        return -1;
    }

    // now we will not use it anymore
    free(request);

    struct pbc_slice slice;

    // read response
    response_type_t response_type;
    response_type = recv_rpc_response(proxy, (char**)(&(slice.buffer)), &(slice.len));
    if (RESPONSE_SUCCEED == response_type) {
        // read response
        struct pbc_rmessage* rmsg = pbc_rmessage_new(env, "GetNewApplicationResponseProto", &slice);
        if (!rmsg) {
            printf("deserialize GetNewApplicationResponseProto from buffer failed.\n");
            free(slice.buffer);
            return -1;
        }
        struct pbc_rmessage* id = pbc_rmessage_message(rmsg, "application_id", 0);
        if (!id) {
            printf("deserialize application_id from GetNewApplicationResponseProto failed.\n");
            pbc_rmessage_delete(rmsg);
            return -1;
        }
        proxy->app_id = pbc_rmessage_integer(id, "id", 0, 0);
        return 0;
    } else {
        process_bad_rpc_response(proxy, response_type);
        return -1;
    }
}

/* ClientRMProtocol.getNewApplication */
static int generate_new_app_request(char** buffer, int* size) {
    int rc;
    struct pbc_wmessage* new_app_request = pbc_wmessage_new(env, "GetNewApplicationRequestProto");
    struct pbc_slice slice;
    pbc_wmessage_buffer(new_app_request, &slice);

    /* try to create HadoopRpcRequestProto */
    rc = generate_hadoop_request((const char*)(slice.buffer), 
        slice.len, 
        CLIENT_RM_PROTOCOL_NAME, 
        GET_NEW_APPLICATION_METHOD_NAME,
        buffer,
        size);
    if (0 != rc) {
        printf("create HadoopRpcRequestProto failed.\n");
        pbc_wmessage_delete(new_app_request);
        return -1;
    }

    pbc_wmessage_delete(new_app_request);
    return 0;
}