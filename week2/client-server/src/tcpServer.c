#include "headers.h"

int check_invalid(int sockfd) {
    if (sockfd == -1) {
        return 1;
    } else {
        return 0;
    }
}

int start_server(int port_num) {
    int sockfd;
    socklen_t len; //store size of the address
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (check_invalid(sockfd)) {
             0;
    }
    bzero((char*) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_num);

     //bind socket
    if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Can't bind to the port %d.\n", port_num);
        return 0;
    }
    return sockfd;
}