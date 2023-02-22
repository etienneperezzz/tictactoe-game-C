CC=gcc
CFLAGS= -Wall -Werror 
LDFLAGS=
EXEC= ../bin/etape_2 

all : $(EXEC)

../bin/etape_2: main.o game.o board.o board_view.o player_manager_scanf.o
	$(CC) -o ../bin/etape_2 main.o game.o board.o board_view.o player_manager_scanf.o $(CFLAGS)

player_manager_scanf.o: player_manager_scanf.c player_manager_scanf.h 
	$(CC) -o player_manager_scanf.o -c player_manager_scanf.c $(CFLAGS)

board.o: board.c board.h
	$(CC) -o board.o -c board.c $(CFLAGS)

main.o: main.c
	$(CC) -o main.o -c main.c  $(CFLAGS)

game.o: game.c game.h
	$(CC) -o game.o -c game.c $(CFLAGS)

board_view.o: board_view_text.c board_view.h
	$(CC) -o board_view.o -c board_view_text.c  $(CFLAGS)

clean:
	rm *.o
