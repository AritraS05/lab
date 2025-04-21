#ifndef OPT_SLIDE_H
#define OPT_SLIDE_H

#define MAX_DATA_SIZE 1024
#define MAX_SEQ 7
#define WINDOW_SIZE 4

typedef struct {
    char data[MAX_DATA_SIZE];
} Packet;

typedef struct {
    int seq_no;
    Packet packet;
    int checksum;
} Frame;

typedef struct {
    int ack_no;
    int framing_bit; // 0 = low buffer, 1 = healthy
    int checksum;
} ACK;

#endif

