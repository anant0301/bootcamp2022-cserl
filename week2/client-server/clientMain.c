#include "headers.h"
#include "tcpClient.h"

int server_sockfd;
void signal_handler(int sigNum) {
    printf("Closing connection...\n");
    close(server_sockfd);
    exit(1);
}

int main(int argc, char * argv[]) {
    signal(SIGINT, signal_handler);
    signal(SIGKILL, signal_handler);
    int port;
    char * host;
    if (argc == 3) {
        host = argv[1];
        port = atoi(argv[2]);
    } else {
        printf("input format: <exec> <server-addr> <server-port>");
        return -1;
    }
    server_sockfd = connect_server(port, host);
    if (server_sockfd == -1) {
        return -1;
    }
    char buffer[BUFFER_SIZE];
    printf("Connected to server..\n");
    while (strcmp(buffer, "q\n")){
        bzero(buffer, BUFFER_SIZE);
        printf("Enter message to pass to server: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        write(server_sockfd, buffer, BUFFER_SIZE);
    }
    printf("Closing connection...\n");
    close(server_sockfd);

    return 0;
}