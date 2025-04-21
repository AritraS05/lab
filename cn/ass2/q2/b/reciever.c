#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "protocol.h"

#define PORT 8080

int calculate_checksum(Frame *f) {
    int sum = f->seq_no + f->ack;
    for (int i = 0; i < strlen(f->packet.data); i++)
        sum += f->packet.data[i];
    return sum;
}

void send_ack(int sockfd, int seq, struct sockaddr_in *sender_addr) {
    Frame ack;
    ack.seq_no = seq;
    ack.ack = 1;
    ack.checksum = calculate_checksum(&ack);
    sendto(sockfd, &ack, sizeof(Frame), 0, (struct sockaddr *)sender_addr, sizeof(*sender_addr));
    printf("ACK %d sent\n", seq);
}

int main() {
    int sockfd;
    struct sockaddr_in receiver_addr, sender_addr;
    Frame f;
    socklen_t len = sizeof(sender_addr);
    int expected_seq = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT);
    receiver_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr));

    while (1) {
        recvfrom(sockfd, &f, sizeof(Frame), 0, (struct sockaddr *)&sender_addr, &len);
        printf("Received frame with seq %d\n", f.seq_no);

        if (f.checksum != calculate_checksum(&f)) {
            printf("Corrupted frame! Ignored.\n");
            continue; // ignore, simulate discard
        }

        if (f.seq_no == expected_seq) {
            printf("Delivered: %s\n", f.packet.data);
            send_ack(sockfd, expected_seq, &sender_addr);
            expected_seq = (expected_seq + 1) % 2;
        } else {
            printf("Duplicate frame! Resending ACK.\n");
            send_ack(sockfd, (expected_seq + 1) % 2, &sender_addr);
        }
    }

    close(sockfd);
    return 0;
}

