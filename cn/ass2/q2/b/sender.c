#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#include "protocol.h"

#define PORT 8080
#define TIMEOUT_SEC 2

int calculate_checksum(Frame *f) {
    int sum = f->seq_no + f->ack;
    for (int i = 0; i < strlen(f->packet.data); i++)
        sum += f->packet.data[i];
    return sum;
}

void send_frame_with_possible_loss(Frame *f, int sockfd, struct sockaddr_in *receiver_addr) {
    double p = (double)rand() / RAND_MAX;

    // Simulate loss
    if (p < 0.2) {
        printf("Simulating frame loss...\n");
        return; // Don't send
    }

    // Simulate corruption
    if (p < 0.4) {
        printf("Simulating corruption...\n");
        f->checksum += 1;
    }

    sendto(sockfd, f, sizeof(Frame), 0, (struct sockaddr *)receiver_addr, sizeof(*receiver_addr));
    printf("Sent frame with seq %d\n", f->seq_no);
}

int wait_for_ack(int sockfd, int expected_seq) {
    Frame ack;
    struct sockaddr_in from;
    socklen_t len = sizeof(from);

    fd_set readfds;
    struct timeval timeout = {TIMEOUT_SEC, 0};

    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);

    int activity = select(sockfd + 1, &readfds, NULL, NULL, &timeout);

    if (activity <= 0) {
        printf("Timeout! No ACK received.\n");
        return 0; // Timeout
    }

    recvfrom(sockfd, &ack, sizeof(Frame), 0, (struct sockaddr *)&from, &len);

    if (ack.ack == 1 && ack.seq_no == expected_seq) {
        printf("Received valid ACK for seq %d\n", ack.seq_no);
        return 1;
    } else {
        printf("Received wrong or corrupted ACK.\n");
        return 0;
    }
}

int main() {
    srand(time(NULL));
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
        printf("Enter message: ");
        fgets(p.data, MAX_DATA_SIZE, stdin);
        p.data[strcspn(p.data, "\n")] = 0;

        f.seq_no = seq;
        f.ack = 0;
        f.packet = p;
        f.checksum = calculate_checksum(&f);

        while (1) {
            send_frame_with_possible_loss(&f, sockfd, &receiver_addr);

            if (wait_for_ack(sockfd, seq)) {
                break; // Move to next frame
            }

            printf("Resending frame with seq %d\n", seq);
        }

        seq = (seq + 1) % 2; // Toggle seq
    }

    close(sockfd);
    return 0;
}

