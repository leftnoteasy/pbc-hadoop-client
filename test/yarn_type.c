#include "pbc_utils.h"
#include "ext/pbc/pbc.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

static void
test_rmessage(struct pbc_env *env, struct pbc_slice *slice) {
    struct pbc_rmessage * m = pbc_rmessage_new(env, "LocalResourceProto", slice);
    if (m==NULL) {
        printf("Error : %s",pbc_error(env));
        return;
    }
    printf("size = %d\n", pbc_rmessage_integer(m , "size" , 0 , NULL));
    printf("ts = %d\n", pbc_rmessage_integer(m , "timestamp" , 0 , NULL));
    printf("pattern = %s\n", pbc_rmessage_string(m , "pattern" , 0 , NULL));

    struct pbc_rmessage* url = pbc_rmessage_message(m, "resource", 0);
    printf("scheme = %s\n", pbc_rmessage_string(url, "scheme", 0, NULL));

    pbc_rmessage_delete(m);
}

static struct pbc_wmessage *
test_wmessage(struct pbc_env * env) {
    struct pbc_wmessage * msg = pbc_wmessage_new(env, "LocalResourceProto");

    pbc_wmessage_integer(msg, "size", 123455432, 0);
    pbc_wmessage_integer(msg, "timestamp" , 99999999, 0);
    pbc_wmessage_string(msg, "pattern", "pattern-pattern", -1);

    struct pbc_wmessage * url = pbc_wmessage_message(msg, "resource");
    pbc_wmessage_string(url , "scheme", "ftp" , -1);
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
