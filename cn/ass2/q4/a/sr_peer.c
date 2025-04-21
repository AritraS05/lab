#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <fcntl.h>
#include "sr_protocol.h"

#define TIMEOUT_SEC 3

int calculate_checksum(Frame *f) {
    int sum = f->seq_no + f->ack_no + f->is_ack;
    for (int i = 0; i < strlen(f->packet.data); i++)
        sum += f->packet.data[i];
    return sum;
}

void send_frame(int sockfd, Frame *f, struct sockaddr_in *dest) {
    double drop_prob = (double)rand() / RAND_MAX;
    if (drop_prob < 0.2) {
        printf("[X] Dropped frame seq %d (simulated)\n", f->seq_no);
        return;
    }
    sendto(sockfd, f, sizeof(Frame), 0, (struct sockaddr *)dest, sizeof(*dest));
    printf("[>] Sent: Seq %d | ACK: %d | is_ack: %d\n", f->seq_no, f->ack_no, f->is_ack);
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
    Frame window[WINDOW_SIZE] = {0};
    int acked[MAX_SEQ + 1] = {0};
    time_t timers[MAX_SEQ + 1] = {0};

    while (base < msg_count) {
        // send frames within window
        while (next_seq < base + WINDOW_SIZE && next_seq < msg_count) {
            Frame f = {0};
            f.seq_no = next_seq % (MAX_SEQ + 1);
            strcpy(f.packet.data, messages[next_seq]);
            f.is_ack = 0;
            f.checksum = calculate_checksum(&f);

            window[f.seq_no] = f;
            timers[f.seq_no] = time(NULL);

            send_frame(sockfd, &f, &remote_addr);
            next_seq++;
        }

        // Wait for ACK or timeout
        fd_set readfds;
        struct timeval timeout = {1, 0};  // check every second
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);

        int activity = select(sockfd + 1, &readfds, NULL, NULL, &timeout);

        if (activity > 0) {
            Frame recv_f;
            recvfrom(sockfd, &recv_f, sizeof(Frame), 0, (struct sockaddr *)&remote_addr, &addr_len);

            if (recv_f.checksum != calculate_checksum(&recv_f)) {
                printf("[!] Corrupted ACK received\n");
                continue;
            }

            if (recv_f.is_ack) {
                printf("[<] ACK received: %d\n", recv_f.ack_no);
                acked[recv_f.ack_no] = 1;

                // slide window if base acked
                while (acked[base % (MAX_SEQ + 1)]) {
                    base++;
                }
            } else {
                // Received data frame (reply)
                printf("[✓] Received DATA: %s (seq %d)\n", recv_f.packet.data, recv_f.seq_no);

                // Send ACK for it
                Frame ack = {.ack_no = recv_f.seq_no, .is_ack = 1};
                ack.checksum = calculate_checksum(&ack);
                send_frame(sockfd, &ack, &remote_addr);
            }
        }

        // Check for timeout
        time_t now = time(NULL);
        for (int i = base; i < next_seq; i++) {
            int seq = i % (MAX_SEQ + 1);
            if (!acked[seq] && difftime(now, timers[seq]) >= TIMEOUT_SEC) {
                printf("[!] Timeout: Resending seq %d\n", seq);
                timers[seq] = now;
                send_frame(sockfd, &window[seq], &remote_addr);
            }
        }
    }

    printf("[*] All messages sent and acknowledged.\n");
    close(sockfd);
    return 0;
}

