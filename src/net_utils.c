#include "net_utils.h"

// 2-byte number
short short_endian_swap(short i) {
    return ((i>>8)&0xff)+((i << 8)&0xff00);
}

// 4-byte number
int int_endian_swap(int i) {
    return ((i&0xff)<<24)+((i&0xff00)<<8)+((i&0xff0000)>>8)+((i>>24)&0xff);
}

// swap endian for an int and write it to socket
void write_endian_swap_int(int socket, int num) {
    int len_for_send = int_endian_swap(num);
    write(socket, &(len_for_send), 4);
}

// swap endian for a short and write it to socket
void write_endian_swap_short(int socket, short num) {
    short len_for_send = short_endian_swap(num);
    write(socket, &(len_for_send), 2);   
}

// write protobuf-style varint-int to buffer
int write_raw_varint32(char* buffer, int value) {
    int index = 0;
    while (1) {
        if ((value & ~0x7F) == 0) {
            buffer[index] = (char)value;
            index++;
            return index;
        } else {
            buffer[index] = (char)((value & 0x7F) | 0x80);
            index++;
            value >>= 7;
        }
    }
    return index;
}