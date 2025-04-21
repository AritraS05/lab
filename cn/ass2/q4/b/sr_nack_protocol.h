#ifndef SR_NACK_PROTOCOL_H
#define SR_NACK_PROTOCOL_H

#define MAX_DATA_SIZE 1024
#define WINDOW_SIZE 4
#define MAX_SEQ 7

typedef struct {
    char data[MAX_DATA_SIZE];
} Packet;

typedef struct {
    int seq_no;
    int is_ack;
    int is_nack;
    Packet packet;
    int checksum;
} Frame;

#endif

