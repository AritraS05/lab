#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "172.23.28.193"  // Replace with the ip shown under eth0 after running "ip addr show"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    const char *msg = "Hello from UDP client!";
    sendto(sockfd, msg, strlen(msg), 0, (const struct sockaddr *)&server_addr, addr_len);
    printf("Message sent to server.\n");

    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
    buffer[n] = '\0';
    printf("Server reply: %s\n", buffer);

    close(sockfd);
    return 0;
}

