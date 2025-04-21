#ifndef PROTOCOL_H
#define PROTOCOL_H

#define MAX_DATA_SIZE 1024
#define WINDOW_SIZE 4
#define MAX_SEQ 7 // should be ≥ 2 * WINDOW_SIZE

typedef struct {
    char data[MAX_DATA_SIZE];
} Packet;

typedef struct {
    int seq_no;
    int type; // 0 = DATA, 1 = ACK, 2 = NACK
    Packet packet;
    int checksum;
} Frame;

#endif

