CC=gcc
CFLAGS= -Wall -Werror
LDFLAGS=
EXEC=main

all : realclean $(EXEC) clean

main : main.o test_CheckEndOfGame.o
	$(CC) -o main main.o test_CheckEndOfGame.o $(LDFLAGS)

main.o: main.c 
	$(CC) -o main.o -c main.c  $(CFLAGS)

test_CheckEndOfGame.o: test_CheckEndOfGame.c test_CheckEndOfGame.h
	$(CC) -o test_CheckEndOfGame.o -c test_CheckEndOfGame.c  $(CFLAGS)

clean:
	rm *.o

realclean: 
	rm $(EXEC)