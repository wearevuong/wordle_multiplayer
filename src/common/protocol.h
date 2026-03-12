#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>
#include <winsock2.h>
#include <windows.h>

#define MAX_PAYLOAD_SIZE 4096

// Initialize and cleanup Winsock
int init_winsock(void);
void cleanup_winsock(void);

// Send and receive length-prefixed messages over TCP
int send_msg(SOCKET sock, const char* payload);
int recv_msg(SOCKET sock, char* payload_out, int max_len);

#endif // PROTOCOL_H
