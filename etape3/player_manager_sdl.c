/**
 * @file player_manager_sdl.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "board.h"
#include "board_view.h"
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#ifndef CONFIG_PLAYER_MANAGER_SDL
#define CONFIG_PLAYER_MANAGER_SDL

#define HEIGHT 480
#define WIDTH 480
#define SQUARE_SIZE 153

static int i;
static PieceType PlayerTurn;
// static bool waiting_for_click = true;

void PlayerManager_init (void)
{
	assert (SDL_WasInit (SDL_INIT_VIDEO) != 0);

	// Initialize the random number generator with the current time
	srand(time(NULL));
	
	// Initialize i randomly to 1 or 2
	i = rand() % 2 + 1;
	PlayerTurn = (i % 2) + 1;
}

void PlayerManager_free (void)
{
	
}

static bool tryMove (int x, int y)
{
	x /= SQUARE_SIZE;
    y /= SQUARE_SIZE;
	if (Board_putPiece(x, y, PlayerTurn) == PIECE_IN_PLACE){
		return true;
	} else {
		return false;
	}
}

void PlayerManager_oneTurn (void)
{
	int error, x, y;
	SDL_Event event;
	bool validMove;
	do
	{
		validMove = false;
		error = SDL_WaitEvent (&event);
		if (error != 1){
			exit(1);
		}
		switch (event.type)
		{
			case SDL_QUIT:
				// TODO:  Fermeture de la fenêtre = quitter l'application
				exit(1);
				break;
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&x, &y);
				if (true == tryMove(x,y)){
					i++;
					PlayerTurn = (i % 2) + 1;
					SDL_Delay(1000);
					BoardView_displayPlayersTurn(PlayerTurn);
				}else {
					validMove = false;
					BoardView_sayCannotPutPiece();
				}
				break;
			default:
				break;
		}
	}
	while (!validMove);
}

#endif
