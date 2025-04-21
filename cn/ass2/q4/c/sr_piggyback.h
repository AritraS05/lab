#ifndef SR_PIGGYBACK_H
#define SR_PIGGYBACK_H

#define MAX_DATA_SIZE 1024
#define WINDOW_SIZE 4
#define MAX_SEQ 7

typedef struct {
    char data[MAX_DATA_SIZE];
} Packet;

typedef struct {
    int seq_no;
    int ack_no;       // piggybacked ACK
    int is_ack_valid; // whether the ack_no is valid
    Packet packet;
    int checksum;
} Frame;

#endif

