#ifndef HEADERS
#define HEADERS
#include <queue>
#include <netdb.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 3000
#define BUFFER_SIZE 100
#define MAX_THREADS 3


int check_invalid(int sockfd);

#endif