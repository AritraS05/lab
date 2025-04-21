#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>
#include "protocol.h"

#define PORT 8080
#define TIMEOUT_SEC 3

int calculate_checksum(Frame *f) {
    int sum = f->seq_no + f->type;
    for (int i = 0; i < strlen(f->packet.data); i++)
        sum += f->packet.data[i];
    return sum;
}

void send_frame(Frame *f, int sockfd, struct sockaddr_in *receiver_addr) {
    double p = (double)rand() / RAND_MAX;
    if (p < 0.2) {
        printf("[X] Simulating frame loss for seq %d\n", f->seq_no);
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
    char input[100][MAX_DATA_SIZE];
    int total_packets;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &receiver_addr.sin_addr);

    printf("Enter number of packets: ");
    scanf("%d", &total_packets);
    getchar();

    for (int i = 0; i < total_packets; i++) {
        printf("Packet %d: ", i);
        fgets(input[i], MAX_DATA_SIZE, stdin);
        input[i][strcspn(input[i], "\n")] = 0;
    }

    while (base < total_packets) {
        while (next_seq < base + WINDOW_SIZE && next_seq < total_packets) {
            Frame f;
            f.seq_no = next_seq % (MAX_SEQ + 1);
            f.type = 0; // DATA
            strcpy(f.packet.data, input[next_seq]);
            f.checksum = calculate_checksum(&f);
            window[next_seq % WINDOW_SIZE] = f;
            send_frame(&f, sockfd, &receiver_addr);
            next_seq++;
        }

        // Wait for ACK/NACK
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
            Frame response;
            recvfrom(sockfd, &response, sizeof(Frame), 0, (struct sockaddr *)&receiver_addr, &len);
            if (response.type == 1) { // ACK
                printf("[<] Received ACK %d\n", response.seq_no);
                int acked = (response.seq_no - base + MAX_SEQ + 1) % (MAX_SEQ + 1) + 1;
                base += acked;
            } else if (response.type == 2) { // NACK
                printf("[<] Received NACK %d. Resending from %d\n", response.seq_no, response.seq_no);
                next_seq = base = response.seq_no;
            }
        }
    }

    close(sockfd);
    return 0;
}

