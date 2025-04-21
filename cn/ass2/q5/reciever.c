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

    struct sockaddr_in receiver_addr, sender_addr;
    socklen_t addr_len = sizeof(sender_addr);

    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(6001);
    receiver_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&receiver_addr, sizeof(receiver_addr));

    int expected = 0;
    int buffer_slots = MAX_SEQ; // buffer size = 2^m - 1

    while (1) {
        Frame f;
        if (recvfrom(sockfd, &f, sizeof(f), 0, (struct sockaddr*)&sender_addr, &addr_len) > 0) {
            if (f.checksum != checksum_frame(&f)) {
                printf("Corrupted frame received. Ignored.\n");
                continue;
            }

            if (f.seq_no == expected) {
                printf("Received frame %d: %s\n", f.seq_no, f.packet.data);
                expected = (expected + 1) % (MAX_SEQ + 1);
                buffer_slots--;

                // Send ACK with framing bit
                ACK ack;
                ack.ack_no = f.seq_no;
                ack.framing_bit = buffer_slots > 1 ? 1 : 0;
                ack.checksum = checksum_ack(&ack);
                sendto(sockfd, &ack, sizeof(ack), 0, (struct sockaddr*)&sender_addr, addr_len);
            } else {
                printf("Out-of-order frame (expected %d but got %d). Ignored.\n", expected, f.seq_no);
            }

            if (buffer_slots == 0) {
                buffer_slots = MAX_SEQ; // Reset for simplicity
            }
        }
    }

    close(sockfd);
    return 0;
}

