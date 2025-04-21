#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>
#include "protocol.h"

#define PORT 8080
#define TIMEOUT_SEC 3

int calculate_checksum(Frame *f) {
    int sum = f->seq_no + f->ack;
    for (int i = 0; i < strlen(f->packet.data); i++)
        sum += f->packet.data[i];
    return sum;
}

void send_frame(Frame *f, int sockfd, struct sockaddr_in *receiver_addr) {
    double p = (double)rand() / RAND_MAX;
    if (p < 0.2) {
        printf("[X] Frame %d lost.\n", f->seq_no);
        return;
    }

    sendto(sockfd, f, sizeof(Frame), 0, (struct sockaddr *)receiver_addr, sizeof(*receiver_addr));
    printf("[>] Sent frame %d\n", f->seq_no);
}

int main() {
    srand(time(NULL));

    int sockfd;
    struct sockaddr_in receiver_addr;
    socklen_t len = sizeof(receiver_addr);
    Frame window[WINDOW_SIZE];
    int base = 0, next_seq = 0;
    char input[WINDOW_SIZE][MAX_DATA_SIZE];
    int total_packets;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &receiver_addr.sin_addr);

    printf("Enter number of packets: ");
    scanf("%d", &total_packets);
    getchar();

    for (int i = 0; i < total_packets; i++) {
        printf("Data %d: ", i);
        fgets(input[i], MAX_DATA_SIZE, stdin);
        input[i][strcspn(input[i], "\n")] = 0;
    }

    while (base < total_packets) {
        while (next_seq < base + WINDOW_SIZE && next_seq < total_packets) {
            Frame f;
            f.seq_no = next_seq % (MAX_SEQ + 1);
            f.ack = 0;
            strcpy(f.packet.data, input[next_seq]);
            f.checksum = calculate_checksum(&f);
            window[next_seq % WINDOW_SIZE] = f;
            send_frame(&f, sockfd, &receiver_addr);
            next_seq++;
        }

        // Wait for ACK
        fd_set readfds;
        struct timeval timeout = {TIMEOUT_SEC, 0};
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);

        int activity = select(sockfd + 1, &readfds, NULL, NULL, &timeout);

        if (activity == 0) {
            printf("Timeout! Resending window [%d to %d]\n", base, next_seq - 1);
            for (int i = base; i < next_seq; i++) {
                send_frame(&window[i % WINDOW_SIZE], sockfd, &receiver_addr);
            }
        } else {
            Frame ack;
            recvfrom(sockfd, &ack, sizeof(Frame), 0, (struct sockaddr *)&receiver_addr, &len);
            if (ack.ack == 1 && ack.seq_no >= base % (MAX_SEQ + 1)) {
                printf("[<] ACK %d received\n", ack.seq_no);
                int acked = (ack.seq_no - (base % (MAX_SEQ + 1)) + MAX_SEQ + 1) % (MAX_SEQ + 1) + 1;
                base += acked;
            }
        }
    }

    close(sockfd);
    return 0;
}

