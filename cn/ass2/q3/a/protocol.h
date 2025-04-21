// protocol.h
#ifndef PROTOCOL_H
#define PROTOCOL_H

#define MAX_DATA_SIZE 1024
#define WINDOW_SIZE 4
#define MAX_SEQ 7 // sequence numbers from 0 to MAX_SEQ (modulo arithmetic)

typedef struct {
    char data[MAX_DATA_SIZE];
} Packet;

typedef struct {
    int seq_no;
    int ack; // 0: data frame, 1: ACK
    Packet packet;
    int checksum;
} Frame;

#endif

