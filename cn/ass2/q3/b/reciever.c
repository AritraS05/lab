#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "protocol.h"

#define PORT 8080

int calculate_checksum(Frame *f) {
    int sum = f->seq_no + f->type;
    for (int i = 0; i < strlen(f->packet.data); i++)
        sum += f->packet.data[i];
    return sum;
}

void send_control(int sockfd, int seq, int type, struct sockaddr_in *sender_addr) {
    Frame ctrl;
    ctrl.type = type;
    ctrl.seq_no = seq;
    ctrl.checksum = calculate_checksum(&ctrl);
    sendto(sockfd, &ctrl, sizeof(Frame), 0, (struct sockaddr *)sender_addr, sizeof(*sender_addr));
    if (type == 1)
        printf("[>] Sent ACK %d\n", seq);
    else
        printf("[>] Sent NACK %d\n", seq);
}

int main() {
    int sockfd;
    struct sockaddr_in receiver_addr, sender_addr;
    socklen_t len = sizeof(sender_addr);
    Frame f;
    int expected_seq = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT);
    receiver_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr));

    while (1) {
        recvfrom(sockfd, &f, sizeof(Frame), 0, (struct sockaddr *)&sender_addr, &len);

        if (f.type != 0 || f.checksum != calculate_checksum(&f)) {
            printf("[X] Corrupted frame or not a DATA frame. Sending NACK %d\n", expected_seq);
            send_control(sockfd, expected_seq, 2, &sender_addr); // NACK
            continue;
        }

        if (f.seq_no == expected_seq) {
            printf("[✓] Received: %s (seq %d)\n", f.packet.data, f.seq_no);
            send_control(sockfd, expected_seq, 1, &sender_addr); // ACK
            expected_seq = (expected_seq + 1) % (MAX_SEQ + 1);
        } else {
            printf("[!] Unexpected frame %d (expected %d). Sending NACK\n", f.seq_no, expected_seq);
            send_control(sockfd, expected_seq, 2, &sender_addr); // NACK
        }
    }

    close(sockfd);
    return 0;
}

