#ifndef _HD_CLIENT_NET_UTILS_H
#define _HD_CLIENT_NET_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// 2-byte number
short short_endian_swap(short i);

// 4-byte number
int int_endian_swap(int i);

// swap endian for an int and write it to socket
void write_endian_swap_int(int socket, int num);

// swap endian for a short and write it to socket
void write_endian_swap_short(int socket, short num);

// write protobuf-style varint-int to buffer
int write_raw_varint32(char* buffer, int value)

#endif // _HD_CLIENT_NET_UTILS_H