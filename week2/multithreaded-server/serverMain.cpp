#include "headers.h"
#include "tcpServer.h"
#include "threadPool.h"

TCPServer * server;
ThreadPool * pool;
void * handle_connection(void *);

void signal_handler(int sigNum) {
    printf("Shutting server down...\n");
    exit(1);
}

int main(int argc, char* argv[]) {
    int port;
    int sockfd;
    int n_threads;

    if (argc > 1) {
        port = atoi(argv[1]);
    } else {
        return -1;
    }
    std::cout << "Server port " << port << std::endl;

    // singal for interrupt detection
    signal(SIGINT, signal_handler);
    signal(SIGKILL, signal_handler);

    // initialize server
    server = new TCPServer(port);
    server-> initialize_port();
    std::cout << "The server initialized..." << std::endl;

    // initialize thread pool
    pool = new ThreadPool(MAX_THREADS);
    n_threads = pool-> declare_runner(handle_connection);
    std::cout << "The server is running on " << n_threads << " Threads" << std::endl;

    while (1) {
        sockfd = server-> accept_connections();
        std::cout << "New client Connection accepted" << std::endl;
        if  (sockfd == -1) {
            std::cout << "Error in client connection" << std::endl;
        } else {
            sem_post(&(pool-> sem));
        }
    }
    return 0;
}

void * handle_connection(void *) {
    int client_sock;
    while (1) {
        sem_wait(&(pool-> sem));
        pthread_mutex_lock(&(pool-> lock));
        client_sock = server-> get_socket();
        pthread_mutex_unlock(&(pool-> lock));
        if (client_sock) {
            server-> simple_client_connect(client_sock);
        } else {
            std::cout << "0 in connection queue" << std::endl;
        }
    }
}