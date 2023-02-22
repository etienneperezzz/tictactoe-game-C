/**
 * @file main.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "player_manager_sdl.h"
#include "board_view.h"
#include "board.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define BOARD_SIZE 3 

PieceType board[BOARD_SIZE][BOARD_SIZE];

static bool game_ended = false;

void Game_onSquareChange(Coordinate x, Coordinate y, PieceType newContent) {
  BoardView_displaySquare(x, y, newContent);
}

void Game_onEndOfGame(GameResult result) {
  game_ended = true;
  BoardView_displayEndOfGame(result);
}

void Game_init(void)
{
  BoardView_init();
  Board_init(Game_onSquareChange, Game_onEndOfGame);
  PlayerManager_init();
}

void Game_free(void)
{
  BoardView_free();
  Board_free();
  PlayerManager_free();
}

void Game_loop(void)
{
  BoardView_displayAll();
    while (!game_ended){
      PlayerManager_oneTurn();
    }
}
