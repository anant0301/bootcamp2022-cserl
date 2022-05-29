all: server

HEADERS = ./include/tcpServer.h ./include/threadPool.h ./include/headers.h
TARGETS = server
FLAGS = -Wall -Iinclude -lpthread
CC = g++

server: serverMain.cpp
	g++ -Iinclude -o server serverMain.cpp ./src/* -lpthread

clean:
	rm -f $(TARGETS)