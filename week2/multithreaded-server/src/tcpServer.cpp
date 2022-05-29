#include "tcpServer.h"


int check_invalid(int retval) {
    if (retval == -1) {
        return 1;
    } else {
        return 0;
    }
}

TCPServer::TCPServer(const int port_num) {
    this-> port = port_num;
    this-> server_len = sizeof(struct sockaddr_in);
}

const int TCPServer::cleanup() {
    int x;
    while(!this-> connections.empty()) {
        x = this-> connections.front();
        close(x);
        std::cout << "Connection Closed: " << x << std::endl;
        this-> connections.pop();
    }
    close(this-> sockfd);
    std::cout << "Server shutdown..." << std::endl;
    return 1;
}

TCPServer::~TCPServer() {
    this-> cleanup();
}

const int TCPServer::initialize_port() {
    this-> sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (check_invalid(sockfd)) {
        std::cout << "Unable to create socket\n";
        return -1;
    }
    this-> server_addr.sin_family = AF_INET;
    this-> server_addr.sin_port = htons(port);
    this-> server_addr.sin_addr.s_addr = INADDR_ANY;

    if(check_invalid(bind(this-> sockfd, (struct sockaddr *)&(this-> server_addr), this-> server_len))) {
        std::cout << "Can't bind to the port number " << this-> port << std::endl;
        return -1;
    }
    return 1;
}

const int TCPServer::accept_connections() {
    int clientfd;
    listen(this-> sockfd, 3);
    std::cout << "Server Listening.. " << std::endl;
    struct sockaddr_in client_addr;
    // should be looping through this
    socklen_t clientlen = sizeof(client_addr);
    clientfd = accept(this-> sockfd, (struct sockaddr *)&client_addr, &clientlen);
    if (check_invalid(clientfd)) {
        return -1;
    }
    pthread_mutex_lock(&(this-> lock));
    this-> connections.push(clientfd);
    pthread_mutex_unlock(&(this-> lock));
    return clientfd;
}

void TCPServer::simple_client_connect(int client_sock) {
    // int client_sock = *((int *) ptr);
    char buffer[BUFFER_SIZE];
    while (strcmp(buffer, "q\n")) {
        bzero(buffer, BUFFER_SIZE);
        read(client_sock, buffer, BUFFER_SIZE);
        printf("Message Received from client: %s\n", buffer);
    }
    close(client_sock);
}

int TCPServer::get_socket() {
    if (this-> connections.empty()) {
        return 0;
    }
    int client_sock;
    pthread_mutex_lock(&(this-> lock));
    client_sock = this-> connections.front();
    this-> connections.pop();
    pthread_mutex_unlock(&(this-> lock));
    return client_sock;
}