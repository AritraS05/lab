#ifndef PROTOCOL_H
#define PROTOCOL_H

#define MAX_DATA_SIZE 1024

typedef struct {
    char data[MAX_DATA_SIZE];
} Packet;

typedef struct {
    int seq_no;
    int ack; // 0: frame, 1: ack
    Packet packet;
    int checksum; // to simulate corruption
} Frame;

#endif

