#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
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
    ack.ack = 1;
    ack.seq_no = seq;
    ack.checksum = calculate_checksum(&ack);
    sendto(sockfd, &ack, sizeof(Frame), 0, (struct sockaddr *)sender_addr, sizeof(*sender_addr));
    printf("[>] ACK %d sent\n", seq);
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

        if (f.ack != 0 || f.checksum != calculate_checksum(&f)) {
            printf("[X] Corrupted or invalid frame\n");
            continue;
        }

        if (f.seq_no == expected_seq) {
            printf("[✓] Received: %s (seq %d)\n", f.packet.data, f.seq_no);
            send_ack(sockfd, expected_seq, &sender_addr);
            expected_seq = (expected_seq + 1) % (MAX_SEQ + 1);
        } else {
            printf("[!] Out-of-order frame %d (expected %d). Discarded.\n", f.seq_no, expected_seq);
            int last_ack = (expected_seq - 1 + MAX_SEQ + 1) % (MAX_SEQ + 1);
            send_ack(sockfd, last_ack, &sender_addr); // repeat last ACK
        }
    }

    close(sockfd);
    return 0;
}

