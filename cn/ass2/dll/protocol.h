#ifndef PROTOCOL_H
#define PROTOCOL_H

#define MAX_DATA_SIZE 1024

typedef struct {
    char data[MAX_DATA_SIZE];
} Packet;

typedef struct {
    Packet packet;
} Frame;

typedef enum {
    frame_arrival
} EventType;

#endif

