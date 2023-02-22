CC=gcc
CFLAGS= -Wall -Werror
LDFLAGS=
EXEC= ../bin/etape_1 test_player_manager_mock

all : $(EXEC)

../bin/etape_1: main.o game.o board.o board_view.o player_manager_mock.o 
	$(CC) -o ../bin/etape_1 main.o game.o board.o board_view.o player_manager_mock.o $(CFLAGS)

test_player_manager_mock: main_test_player_manager_mock.o test_player_manager_mock.o
	$(CC) -o test_player_manager_mock main_test_player_manager_mock.o test_player_manager_mock.o

player_manager_mock.o: player_manager_mock.c player_manager.h 
	$(CC) -o player_manager_mock.o -c player_manager_mock.c $(CFLAGS)

board.o: board.c board.h
	$(CC) -o board.o -c board.c $(CFLAGS)

main.o: main.c
	$(CC) -o main.o -c main.c  $(CFLAGS)

game.o: game.c game.h
	$(CC) -o game.o -c game.c $(CFLAGS)

board_view.o: board_view_text.c board_view.h
	$(CC) -o board_view.o -c board_view_text.c  $(CFLAGS)

main_test_player_manager_mock.o: main_test_player_manager_mock.c
	$(CC) -o main_test_player_manager_mock.o -c main_test_player_manager_mock.c

test_player_manager_mock.o: test_player_manager_mock.c test_player_manager_mock.h
	$(CC) -o test_player_manager_mock.o -c test_player_manager_mock.c $(CFLAGS)

clean:
	rm *.o
