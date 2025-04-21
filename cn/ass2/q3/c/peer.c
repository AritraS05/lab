#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>
#include "protocol.h"

#define TIMEOUT_SEC 3

int calculate_checksum(Frame *f) {
    int sum = f->seq_no + f->ack_no + f->ack_type;
    for (int i = 0; i < strlen(f->packet.data); i++)
        sum += f->packet.data[i];
    return sum;
}

void send_frame(int sockfd, Frame *f, struct sockaddr_in *dest) {
    double p = (double)rand() / RAND_MAX;
    if (p < 0.2) {
        printf("[X] Simulating frame drop for seq %d\n", f->seq_no);
        return;
    }
    sendto(sockfd, f, sizeof(Frame), 0, (struct sockaddr *)dest, sizeof(*dest));
    printf("[>] Sent: Seq %d (ACK: %d [%s])\n", f->seq_no,
           f->ack_no, f->ack_type == 1 ? "ACK" : f->ack_type == 2 ? "NACK" : "None");
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <local_port> <remote_ip> <remote_port> <role>\n", argv[0]);
        return 1;
    }

    int local_port = atoi(argv[1]);
    char *remote_ip = argv[2];
    int remote_port = atoi(argv[3]);
    char *role = argv[4];

    srand(time(NULL));

    int sockfd;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t addr_len = sizeof(remote_addr);
    Frame window[WINDOW_SIZE];
    int base = 0, next_seq = 0, expected_seq = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&local_addr, 0, sizeof(local_addr));
    memset(&remote_addr, 0, sizeof(remote_addr));

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(local_port);
    local_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr));

    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(remote_port);
    inet_pton(AF_INET, remote_ip, &remote_addr.sin_addr);

    printf("[%s] Ready on port %d. Communicating with %s:%d\n", role, local_port, remote_ip, remote_port);

    char messages[100][MAX_DATA_SIZE];
    int msg_count;
    printf("Enter number of messages to send: ");
    scanf("%d", &msg_count); getchar();

    for (int i = 0; i < msg_count; i++) {
        printf("Message %d: ", i);
        fgets(messages[i], MAX_DATA_SIZE, stdin);
        messages[i][strcspn(messages[i], "\n")] = 0;
    }

    while (base < msg_count || 1) {
        // Send data if within window
        if (next_seq < base + WINDOW_SIZE && next_seq < msg_count) {
            Frame f = {0};
            f.seq_no = next_seq % (MAX_SEQ + 1);
            f.ack_type = 0;
            strcpy(f.packet.data, messages[next_seq]);
            f.checksum = calculate_checksum(&f);
            window[next_seq % WINDOW_SIZE] = f;
            send_frame(sockfd, &f, &remote_addr);
            next_seq++;
        }

        // Listen for frame (data + piggybacked ack/nack)
        fd_set readfds;
        struct timeval timeout = {TIMEOUT_SEC, 0};
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);

        int activity = select(sockfd + 1, &readfds, NULL, NULL, &timeout);

        if (activity == 0) {
            // Timeout
            printf("[!] Timeout, resending window [%d to %d]\n", base, next_seq - 1);
            for (int i = base; i < next_seq; i++) {
                send_frame(sockfd, &window[i % WINDOW_SIZE], &remote_addr);
            }
            continue;
        }

        Frame rcv;
        recvfrom(sockfd, &rcv, sizeof(Frame), 0, (struct sockaddr *)&remote_addr, &addr_len);

        // Validate checksum
        if (rcv.checksum != calculate_checksum(&rcv)) {
            printf("[X] Received corrupt frame\n");
            Frame nack = {.ack_no = expected_seq, .ack_type = 2};
            nack.seq_no = 9999;  // dummy
            nack.checksum = calculate_checksum(&nack);
            send_frame(sockfd, &nack, &remote_addr);
            continue;
        }

        // Process piggybacked ACK
        if (rcv.ack_type == 1) {
            int acked = (rcv.ack_no - base + MAX_SEQ + 1) % (MAX_SEQ + 1) + 1;
            printf("[<] ACK received: %d\n", rcv.ack_no);
            base += acked;
        } else if (rcv.ack_type == 2) {
            printf("[<] NACK received: %d. Resending from there.\n", rcv.ack_no);
            next_seq = base = rcv.ack_no;
        }

        // Process incoming DATA
        if (rcv.seq_no == expected_seq) {
            printf("[✓] Received DATA: %s (seq %d)\n", rcv.packet.data, rcv.seq_no);
            expected_seq = (expected_seq + 1) % (MAX_SEQ + 1);

            // Send piggybacked ACK
            Frame reply = {.ack_type = 1, .ack_no = (expected_seq - 1 + MAX_SEQ + 1) % (MAX_SEQ + 1)};
            reply.seq_no = 9999;  // dummy
            reply.checksum = calculate_checksum(&reply);
            send_frame(sockfd, &reply, &remote_addr);
        } else {
            printf("[!] Unexpected seq %d, expected %d. Sending NACK\n", rcv.seq_no, expected_seq);
            Frame nack = {.ack_type = 2, .ack_no = expected_seq};
            nack.seq_no = 9999;
            nack.checksum = calculate_checksum(&nack);
            send_frame(sockfd, &nack, &remote_addr);
        }

        if (base >= msg_count) break;
    }

    close(sockfd);
    return 0;
}

