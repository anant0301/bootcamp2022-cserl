#include "headers.h"

int check_invalid(int sockfd) {
    if (sockfd == -1) {
        return 1;
    } else {
        return 0;
    }
}

int connect_server(int port_num, char hostname[]) {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (check_invalid(sockfd)) {
        return 0;
    }
    if (gethostbyname(hostname) == NULL) {
        printf("Host <%s> does not exist.", hostname);
        return -1;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_num);
    server_addr.sin_addr.s_addr = inet_addr(hostname);
    // bzero((char *) &server_addr, (int) server_len);
    memset(server_addr.sin_zero, '\0', (int) server_len);

    if (connect(sockfd, (struct sockaddr *) &server_addr, server_len) != 0) {
        printf("connection with the server failed...\n");
        return -1;
    }
    return sockfd;
}