#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>

#define PACKET_SIZE 64

unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return ~sum;
}

int main() {
    int sockfd;
    char packet[PACKET_SIZE];
    struct sockaddr_in dest_addr;

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct icmphdr *icmp_hdr = (struct icmphdr *)packet;
    memset(packet, 0, PACKET_SIZE);
    icmp_hdr->type = ICMP_ECHO; 
    icmp_hdr->code = 0;
    icmp_hdr->un.echo.id = getpid();
    icmp_hdr->un.echo.sequence = 1;
    icmp_hdr->checksum = checksum(icmp_hdr, PACKET_SIZE);

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = 0; 
    inet_pton(AF_INET, "172.23.28.193", &dest_addr.sin_addr); // Replace with server IP under eth0 after running "ip addr show"

    if (sendto(sockfd, packet, PACKET_SIZE, 0,
               (struct sockaddr *)&dest_addr, sizeof(dest_addr)) <= 0) {
        perror("sendto failed");
    } else {
        printf("Raw ICMP packet sent.\n");
    }

    close(sockfd);
    return 0;
}

