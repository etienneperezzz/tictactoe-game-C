/**
 * @file player_manager_scanf.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "board.h"
#include "board_view.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifndef CONFIG_PLAYER_MANAGER_SCANF
#define CONFIG_PLAYER_MANAGER_SCANF

#define MAX_LENGTH 100

static int i;
static PieceType PlayerTurn;

void PlayerManager_init (void)
{
	// Initialise le generateur de nombre aléatoire avec le temps actuel
	srand(time(NULL));
	
	// Initialise i aléatoire entre 1 et 2
	i = rand() % 2 + 1;
	PlayerTurn = (i % 2) + 1;
}

void PlayerManager_free (void)
{
}

void PlayerManager_oneTurn(void)
{
  Coordinate x, y;
  char input[MAX_LENGTH];

  PieceType PlayerTurn = (i % 2) + 1;
  BoardView_displayPlayersTurn(PlayerTurn);

  fgets (input, MAX_LENGTH,stdin);
  if (strlen(input) == 4) {
    // Vérifier si la chaîne respecte le format "int,int" sans espaces
    if (sscanf(input, "%d,%d", &x, &y) == 2) {
		// Vérifier que les coordonnées entrées sont comprises entre 0 et 2 et que la pièce est bien en place
      if (((x >= 0 && x <= 2) && (y >= 0 && y <= 2)) && (Board_putPiece(x, y, PlayerTurn) == PIECE_IN_PLACE)){
        i++;
      }
      // Sinon on redemande au meme joueur de rejouer
      else{
        BoardView_sayCannotPutPiece();
        PlayerTurn--;
      }
    }
  } else {
      // La chaîne ne respecte pas le format, afficher un message d'erreur
      BoardView_sayCannotPutPiece();
      PlayerTurn--;
  }
}

#endif
