#include "ext/pbc/pbc.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

static void
read_file (const char *filename , struct pbc_slice *slice) {
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


static void
dump(uint8_t *buffer, int sz) {
    int i , j;
    for (i=0;i<sz;i++) {
        printf("%02X ",buffer[i]);
        if (i % 16 == 15) {
            for (j = 0 ;j <16 ;j++) {
                char c = buffer[i/16 * 16+j];
                if (c>=32 && c<127) {
                    printf("%c",c);
                } else {
                    printf(".");
                }
            }
            printf("\n");
        }
    }

    printf("\n");
}

static struct pbc_wmessage *
test_wmessage(struct pbc_env * env)
{
    struct pbc_wmessage * msg = pbc_wmessage_new(env, "real");

    pbc_wmessage_real(msg, "f", 1.0);
    pbc_wmessage_real(msg, "d" , 4.0);

    return msg;
}

int connect_to_server(int sockfd, const char* hostname, int portno)
{
    //define socket variables
    struct sockaddr_in serv_addr;
    struct hostent *server;

    //init port / socket / server
    server = gethostbyname(hostname);
    if (server == NULL)
    {
        fprintf(stderr,"ERROR, no such host");
        return -1;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
                server->h_length);
                serv_addr.sin_port = htons(portno);
                 
    //connect via socket
    if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0)
    {
        printf("ERROR connecting");
        return -1;
    }
}

// 2-byte number
short short_endian_swap(short i)
{
    return ((i>>8)&0xff)+((i << 8)&0xff00);
}

// 4-byte number
int int_endian_swap(int i)
{
    return ((i&0xff)<<24)+((i&0xff00)<<8)+((i&0xff0000)>>8)+((i>>24)&0xff);
}

int main()
{
    struct pbc_slice slice;
    read_file("../test/float.pb", &slice);
    if (slice.buffer == NULL)
        return 1;
    struct pbc_env * env = pbc_new();
    pbc_register(env, &slice);

    free(slice.buffer);

    struct pbc_wmessage *msg = test_wmessage(env);

    pbc_wmessage_buffer(msg, &slice);

    // here we got slice, we will send it out
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    connect_to_server(sockfd, "localhost", 8980);

    // size of buffer
    int len_for_send = int_endian_swap(slice.len);
    write(sockfd, &(len_for_send), 4);
    write(sockfd, slice.buffer, slice.len);

    // clear msg end env
    pbc_wmessage_delete(msg);
    pbc_delete(env);

    return 0;
}
