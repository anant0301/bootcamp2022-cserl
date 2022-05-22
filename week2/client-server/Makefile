all: client server

HEADERS = include/tcpServer.h include/client.h include/headers.h
TARGETS = server client
FLAGS = -Wall -Iinclude
CC = gcc

server: serverMain.c src/tcpServer.c include/*
	$(CC) -o server serverMain.c src/tcpServer.c include/* -Iinclude

client: clientMain.c src/tcpClient.c include/*
	$(CC) -o client clientMain.c src/tcpClient.c include/* -Iinclude

clean:
	rm $(TARGETS)