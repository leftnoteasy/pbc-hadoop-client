#ifndef _HD_CLIENT_PBC_UTILS_H
#define _HD_CLIENT_PBC_UTILS_H

#include "ext/pbc/pbc.h"

/*
 * init pbc env, and register pb-dump files from files under dir, 
 * and ends with ".pb".
 * return how many files successfully registered, -1 if failed.
 */
int init_pbc_env_with_dir(const char* dir, struct pbc_env* env);

#endif