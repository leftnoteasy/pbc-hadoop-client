#include "pbc_utils.h"
#include "str_utils.h"

#include "ext/pbc/pbc.h"

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define PATH_MAX 4096 /* max length of a path name including nul */

static void read_file(const char* filename, struct pbc_slice* slice);

int init_pbc_env_with_dir(const char* dir, struct pbc_env* env) {
    DIR* dirp = opendir(dir);
    struct pbc_slice slice;
    struct pbc_slice all_files;
    
    // check if dir can be opened
    if (!dirp) {
        printf("open dir:%s failed\n", dir);
        return -1;
    }

    struct dirent* ent;
    char full_file_name[4066];
    int rc;

    int total_registered_file = 0;
    
    // we will put all files content to this struct
    all_files.buffer = (char*)malloc(2 * 1024 * 1024);

    while ((ent = readdir(dirp)) != NULL) {
        if (ent->d_namlen > 0) {
            // check if file end with ".pb"
            if (str_ends_with(ent->d_name, ".pb")) {
                // try to read this file, and add it to env
                sprintf(full_file_name, "%s/%s", dir, ent->d_name);

                // read this file to slice
                read_file(full_file_name, &slice);

                // copy from slice to total_registered_file
                memcpy(all_files.buffer + all_files.len, slice.buffer, slice.len);
                total_registered_file++;
                all_files.len += slice.len;

                free(slice.buffer);
            }
        }
    }

    rc = pbc_register(env, &all_files);
    if (rc) {
        printf("error when register: %s\n", pbc_error(env));
        return -1;
    }

    free(all_files.buffer);
    closedir(dirp);

    return total_registered_file;
}

// read file to a buffer, will be used for load 
static void read_file(const char *filename , struct pbc_slice* slice) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        slice->buffer = NULL;
        slice->len = 0;
        return;
    }
    fseek(f,0,SEEK_END);
    slice->len = ftell(f);
    fseek(f,0,SEEK_SET);
    slice->buffer = malloc(slice->len);
    fread(slice->buffer, 1 , slice->len , f);
    fclose(f);
}