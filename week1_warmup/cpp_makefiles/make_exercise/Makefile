all: main

CC = g++
C_FLAGS = -Wall -g -O2 -I.
HEADERS = functions.h
TARGETS = main main.o hello.o factorial.o
OBJ = main.o hello.o factorial.o

main: $(OBJ) $(HEADERS)
	$(CC) $(C_FLAGS) $(OBJ) -o main

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(TARGETS)