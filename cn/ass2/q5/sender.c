#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include "opt_slide.h"

int checksum_frame(Frame *f) {
    int sum = f->seq_no;
    for (int i = 0; i < strlen(f->packet.data); i++)
        sum += f->packet.data[i];
    return sum;
}

int checksum_ack(ACK *ack) {
    return ack->ack_no + ack->framing_bit;
}

int main() {
    srand(time(NULL));
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in sender_addr, receiver_addr;
    socklen_t addr_len = sizeof(receiver_addr);

    sender_addr.sin_family = AF_INET;
    sender_addr.sin_port = htons(6000);
    sender_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&sender_addr, sizeof(sender_addr));

    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(6001);
    inet_pton(AF_INET, "127.0.0.1", &receiver_addr.sin_addr);

    char messages[10][MAX_DATA_SIZE];
    int n;
    printf("Enter number of messages: ");
    scanf("%d", &n); getchar();
    for (int i = 0; i < n; i++) {
        printf("Message %d: ", i);
        fgets(messages[i], MAX_DATA_SIZE, stdin);
        messages[i][strcspn(messages[i], "\n")] = 0;
    }

    int base = 0, next_seq = 0;
    int max_sendable = WINDOW_SIZE;

    while (base < n) {
        // Send frames up to allowed window size
        while (next_seq < base + max_sendable && next_seq < n) {
            Frame f;
            f.seq_no = next_seq % (MAX_SEQ + 1);
            strcpy(f.packet.data, messages[next_seq]);
            f.checksum = checksum_frame(&f);
            sendto(sockfd, &f, sizeof(f), 0, (struct sockaddr*)&receiver_addr, sizeof(receiver_addr));
            printf("Sent frame seq %d: %s\n", f.seq_no, f.packet.data);
            next_seq++;
        }

        // Wait for ACK
        ACK ack;
        if (recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr*)&receiver_addr, &addr_len) > 0) {
            if (ack.checksum == checksum_ack(&ack)) {
                printf("ACK received: %d | Framing bit: %d\n", ack.ack_no, ack.framing_bit);
                base = ack.ack_no + 1;
                max_sendable = ack.framing_bit ? WINDOW_SIZE : 1; // adjust based on receiver's buffer
            }
        }
    }

    close(sockfd);
    return 0;
}

