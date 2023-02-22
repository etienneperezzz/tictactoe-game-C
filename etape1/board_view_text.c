#include "board_view.h"
#include <assert.h>
#include <stdio.h>

#ifndef CONFIG_TEXTUI
#define CONFIG_TEXTUI

PieceType boardDisplay[3][3];

void BoardView_init(void)
{
  for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
          boardDisplay[i][j] = ' ';
    }
  }
}

void BoardView_free(void)
{
  for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
          boardDisplay[i][j] = ' ';
    }
  }
}

void BoardView_displayAll (void)
{
  // BoardView_displayPlayersTurn(currentPlayer);
  // BoardView_displaySquare(x, y, kindOfPiece);
}

void BoardView_displaySquare (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
  static char pieceSymbol[] = {' ', 'X', 'O'};
  boardDisplay[x][y] = pieceSymbol[kindOfPiece];
  printf("\n");
  printf("\t   %c    |   %c   |   %c   \n", boardDisplay[0][0], boardDisplay[0][1], boardDisplay[0][2]);
  printf("\t--------+-------+------ \n");
  printf("\t   %c    |   %c   |   %c   \n", boardDisplay[1][0], boardDisplay[1][1], boardDisplay[1][2]);
  printf("\t--------+-------+------ \n");
  printf("\t   %c    |   %c   |   %c   \n", boardDisplay[2][0], boardDisplay[2][1], boardDisplay[2][2]);
  printf("\n");
}

void BoardView_displayEndOfGame (GameResult result)

{
  switch (result){

    case CROSS_WINS:printf("******** Felicitations le joueur CROIX a gagne la partie! ********\n\n\n"); break;

    case CIRCLE_WINS: printf("******** Felicitations le joueur CERCLE a gagne la partie! ********\n\n\n"); break;

    case DRAW: printf("C'est une egalite !\nIl y aura peut-etre un vainqueur a la prochaine partie !\n\n\n"); break;

    default: printf("Il y a peut-etre un probleme. Essayez de redémarrer le jeu.\n\n\n");

  }

}

void BoardView_displayPlayersTurn (PieceType thisPlayer)
{
  switch (thisPlayer){

    case CROSS : printf("C'est au tour de joueur CROIX de jouer !\n\n"); break;

    case CIRCLE : printf("C'est au tour de joueur CERCLE de jouer !\n\n"); break;

    default : printf("Il y a peut-etre un probleme. Essayez de redémarrer le jeu.\n\n"); break;

  } 

}

void BoardView_sayCannotPutPiece (void)
{

  printf("/!\\  Mouvement invalide ! Case deja prise, piece en dehors du jeu ou format invalide.  /!\\\n\tEssayez un autre placement.\n\n\n");

}

#endif // defined CONFIG_TEXTUI