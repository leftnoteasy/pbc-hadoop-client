#include "pbc_utils.h"
#include "ext/pbc/pbc.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

static void
test_rmessage(struct pbc_env *env, struct pbc_slice *slice) {
    struct pbc_rmessage * m = pbc_rmessage_new(env, "hadoop.common.HadoopRpcRequestProto", slice);
    if (m==NULL) {
        printf("Error : %s",pbc_error(env));
        return;
    }
    printf("methodName = %s\n", pbc_rmessage_string(m , "methodName" , 0 , NULL));
    int* buffer = (int*)pbc_rmessage_string(m, "request", 0, NULL);
    printf("request = %d %d\n", buffer[0], buffer[1]);

    pbc_rmessage_delete(m);
}

static struct pbc_wmessage *
test_wmessage(struct pbc_env * env) {
    struct pbc_wmessage * msg = pbc_wmessage_new(env, "hadoop.common.HadoopRpcRequestProto");

    int a[2];
    a[0] = 0;
    a[1] = 3399;
    pbc_wmessage_string(msg, "methodName", "name", -1);
    pbc_wmessage_string(msg , "request", (char*)(&(a[0])) , sizeof(int) * 2);
    return msg;
}

int main(int argc, char** argv) {
    struct pbc_env * env = pbc_new();
    int r = init_pbc_env_with_dir(argv[1], env);

    if (r < 0) {
        printf("load pb files failed.");
        return -1;
    }

    struct pbc_wmessage *msg = test_wmessage(env);

    struct pbc_slice slice;
    pbc_wmessage_buffer(msg, &slice);

    test_rmessage(env, &slice);

    pbc_wmessage_delete(msg);
    pbc_delete(env);

    return 0;
}