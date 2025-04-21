#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include "protocol.h"

#define PORT 8080

EventType WaitForEvent() {
    return frame_arrival;
}

void ReceiveFrame(Frame *f, int sockfd) {
    socklen_t len;
    struct sockaddr_in sender_addr;
    recvfrom(sockfd, f, sizeof(Frame), 0, (struct sockaddr *)&sender_addr, &len);
    printf("Frame received.\n");
}

void ExtractData(Packet *p, Frame f) {
    *p = f.packet;
}

void DeliverData(Packet p) {
    printf("Delivered data: %s\n", p.data);
}

int main() {
    int sockfd;
    struct sockaddr_in receiver_addr;
    Frame f;
    Packet p;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT);
    receiver_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr));

    while (1) {
        if (WaitForEvent() == frame_arrival) {
            ReceiveFrame(&f, sockfd);
            ExtractData(&p, f);
            DeliverData(p);
        }
    }

    close(sockfd);
    return 0;
}

