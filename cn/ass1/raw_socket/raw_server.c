#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <sys/socket.h>

#define BUFFER_SIZE 65536

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    printf("Raw socket server waiting for ICMP packets...\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t data_size = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
        if (data_size < 0) {
            perror("recvfrom failed");
            break;
        }

        struct iphdr *ip_header = (struct iphdr*)buffer;
        printf("Received packet from: %d.%d.%d.%d | Size: %ld bytes\n",
            buffer[12], buffer[13], buffer[14], buffer[15], data_size);
    }

    close(sockfd);
    return 0;
}

