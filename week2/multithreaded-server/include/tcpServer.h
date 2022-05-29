#include "headers.h"

class TCPServer {
private:
    int port;
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t server_len;
    std::queue<int> connections;
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
public:
    TCPServer(const int port_num);
    ~TCPServer();

    const int initialize_port();
    const int accept_connections();
    const int cleanup();
    void simple_client_connect(int client_sock);
    int get_socket();
};