// sr_protocol.h
#ifndef SR_PROTOCOL_H
#define SR_PROTOCOL_H

#define MAX_DATA_SIZE 1024
#define WINDOW_SIZE 4
#define MAX_SEQ 7

typedef struct {
    char data[MAX_DATA_SIZE];
} Packet;

typedef struct {
    int seq_no;
    int ack_no;  // if ack = 1, this holds the ack number
    int is_ack;
    Packet packet;
    int checksum;
} Frame;

#endif

