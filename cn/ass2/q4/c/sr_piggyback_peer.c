#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include "sr_piggyback.h"

int calculate_checksum(Frame *f) {
    int sum = f->seq_no + f->ack_no + f->is_ack_valid;
    for (int i = 0; i < strlen(f->packet.data); i++)
        sum += f->packet.data[i];
    return sum;
}

void send_frame(int sockfd, Frame *f, struct sockaddr_in *dest) {
    double drop_prob = (double)rand() / RAND_MAX;
    if (drop_prob < 0.15) {
        printf("[X] Simulated drop of frame (seq %d)\n", f->seq_no);
        return;
    }

    sendto(sockfd, f, sizeof(Frame), 0, (struct sockaddr *)dest, sizeof(*dest));
    printf("[>] Sent frame seq=%d", f->seq_no);
    if (f->is_ack_valid)
        printf(" (piggybacked ACK: %d)", f->ack_no);
    printf(": %s\n", f->packet.data);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <local_port> <remote_ip> <remote_port> <role>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));
    int local_port = atoi(argv[1]);
    char *remote_ip = argv[2];
    int remote_port = atoi(argv[3]);
    char *role = argv[4];

    int sockfd;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t addr_len = sizeof(remote_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(local_port);
    local_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr));

    memset(&remote_addr, 0, sizeof(remote_addr));
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(remote_port);
    inet_pton(AF_INET, remote_ip, &remote_addr.sin_addr);

    printf("[%s] Listening on port %d\n", role, local_port);

    char messages[100][MAX_DATA_SIZE];
    int msg_count;
    printf("Enter number of messages: ");
    scanf("%d", &msg_count); getchar();

    for (int i = 0; i < msg_count; i++) {
        printf("Message %d: ", i);
        fgets(messages[i], MAX_DATA_SIZE, stdin);
        messages[i][strcspn(messages[i], "\n")] = 0;
    }

    int base = 0;
    int next_seq = 0;
    Frame window[MAX_SEQ + 1];
    int acked[MAX_SEQ + 1] = {0};
    int last_ack_received = -1;

    while (base < msg_count || last_ack_received < msg_count - 1) {
        // Send new frames
        while (next_seq < base + WINDOW_SIZE && next_seq < msg_count) {
            Frame f = {0};
            f.seq_no = next_seq % (MAX_SEQ + 1);
            f.is_ack_valid = (last_ack_received >= 0);
            f.ack_no = last_ack_received % (MAX_SEQ + 1);
            strcpy(f.packet.data, messages[next_seq]);
            f.checksum = calculate_checksum(&f);
            send_frame(sockfd, &f, &remote_addr);
            window[f.seq_no] = f;
            next_seq++;
        }

        // Wait for response
        fd_set readfds;
        struct timeval timeout = {3, 0};
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);

        int activity = select(sockfd + 1, &readfds, NULL, NULL, &timeout);
        if (activity > 0) {
            Frame recv_f;
            recvfrom(sockfd, &recv_f, sizeof(Frame), 0, (struct sockaddr *)&remote_addr, &addr_len);

            int valid_checksum = (recv_f.checksum == calculate_checksum(&recv_f));
            if (!valid_checksum) {
                printf("[!] Corrupted frame received — Ignored\n");
                continue;
            }

            if (recv_f.is_ack_valid) {
                printf("[<] Piggybacked ACK received for seq %d\n", recv_f.ack_no);
                acked[recv_f.ack_no] = 1;
                while (acked[base % (MAX_SEQ + 1)])
                    base++;
            }

            if (strlen(recv_f.packet.data) > 0) {
                printf("[✓] Received: %s (seq %d)\n", recv_f.packet.data, recv_f.seq_no);
                last_ack_received = recv_f.seq_no;
            }
        }
    }

    printf("[✔] Communication complete.\n");
    close(sockfd);
    return 0;
}

