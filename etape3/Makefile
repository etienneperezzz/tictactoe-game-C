CC=gcc
CFLAGS= -Wall -Werror 
LDFLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
EXEC= ../bin/etape_3 

all : $(EXEC)

../bin/etape_3: main.o game.o board.o board_view_sdl.o player_manager_sdl.o tictactoe_errors.o
	$(CC) -o ../bin/etape_3 main.o game.o board.o board_view_sdl.o player_manager_sdl.o tictactoe_errors.o $(LDFLAGS)

player_manager_sdl.o: player_manager_sdl.c player_manager_sdl.h 
	$(CC) -o player_manager_sdl.o -c player_manager_sdl.c $(CFLAGS)

board.o: board.c board.h
	$(CC) -o board.o -c board.c $(CFLAGS)

main.o: main.c
	$(CC) -o main.o -c main.c  $(CFLAGS)

game.o: game.c game.h
	$(CC) -o game.o -c game.c $(CFLAGS)

board_view_sdl.o: board_view_sdl.c board_view.h
	$(CC) -o board_view_sdl.o -c board_view_sdl.c $(CFLAGS)

tictactoe_errors.o: tictactoe_errors.c tictactoe_errors.h
	$(CC) -o tictactoe_errors.o -c tictactoe_errors.c $(CFLAGS)

clean:
	rm *.o
