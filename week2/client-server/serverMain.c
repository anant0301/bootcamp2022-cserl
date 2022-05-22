#include "headers.h"
#include "tcpServer.h"

int server_sockfd;
void signal_handler(int sigNum) {
    printf("Shutting server down...\n");
    close(server_sockfd);
    exit(1);
}

int main(int argc, char* argv[]) {
    // singal for interrupt detection
    signal(SIGINT, signal_handler);
    signal(SIGKILL, signal_handler);
    int port;
    int clientfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);
    if (argc >= 2) {
        port = atoi(argv[1]);
    } else {
        port = SERVER_PORT;
    }
    server_sockfd = start_server(port);
    if (server_sockfd == 0) {
        return -1;
    }
    listen(server_sockfd, 3);
    clientfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &clientlen);
    printf("Client Connection accepted\n");
    while (strcmp(buffer, "q\n")) {
        bzero(buffer, BUFFER_SIZE);
        read(clientfd, buffer, BUFFER_SIZE);
        printf("Message Received from client: %s\n", buffer);
    }
    close(clientfd);
    close(server_sockfd);

    return 0;
}