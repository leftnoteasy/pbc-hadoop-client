#include "pbc_utils.h"

#include "ext/pbc/pbc.h"

#include <stdio.h>

int main(int argc, char** argv) {
    if (argc == 0) {
        printf("specify folder contains .pb file plz\n");
        return -1;
    }

    char* folder = argv[1];
    struct pbc_new* env = pbc_new();

    int registered = init_pbc_env_with_dir(folder, env);
    if (registered < 0) {
        printf("register with folder failed, please check");
        return -1;
    }

    printf("%d files successfully registerd.\n", registered);
    return 0;
}