#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "protocol.h"

#define PORT 8080

void GetData(Packet *p) {
    printf("Enter message to send: ");
    fgets(p->data, MAX_DATA_SIZE, stdin);
    p->data[strcspn(p->data, "\n")] = 0;
}

void MakeFrame(Frame *f, Packet p, int seq) {
    f->packet = p;
    f->seq_no = seq;
}

void SendFrame(Frame *f, int sockfd, struct sockaddr_in *receiver_addr) {
    sendto(sockfd, f, sizeof(Frame), 0, (struct sockaddr *)receiver_addr, sizeof(*receiver_addr));
    printf("Frame with seq #%d sent.\n", f->seq_no);
}

void WaitForAck() {
    sleep(1);
}

int main() {
    int sockfd;
    struct sockaddr_in receiver_addr;
    Packet p;
    Frame f;
    int seq = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &receiver_addr.sin_addr);

    while (1) {
        GetData(&p);
        MakeFrame(&f, p, seq);
        SendFrame(&f, sockfd, &receiver_addr);
        WaitForAck(); 
        seq = (seq + 1) % 2;
    }

    close(sockfd);
    return 0;
}

