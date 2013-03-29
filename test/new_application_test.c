#include "hadoop_rpc.h"

#include <stdlib.h>

int main(int argc, char** argv) {
    int rc;
    rc = init_pb_env(argv[1], "2.0.3-alpha");
    if (0 != rc) {
        printf("init pbc env failed.\n");
        return -1;
    }

    hadoop_rpc_proxy_t* proxy = new_hadoop_rpc_proxy(
        argv[2], // host
        atoi(argv[3]), // port
        CLIENT,
        RM);

    if (!proxy) {
        printf("get proxy failed.\n");
        return -1;
    }

    rc = submit_application(proxy, NULL);
    if (rc != 0) {
        printf("submit application failed.\n");
        return -1;
    }

    printf("got app-id:%d\n", proxy->app_id);

    return 0;
}