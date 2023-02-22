/**
 * @file player_manager_mock.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */
#ifndef CONFIG_PLAYER_MANAGER_MOCK
#define CONFIG_PLAYER_MANAGER_MOCK

#include "board.h"
#include <assert.h>
#include <stdio.h>


void PlayerManager_init (void)
{

}


void PlayerManager_free (void)
{
	
}

void PlayerManager_oneTurn (void)
{
	char * error_message = "/!\\  Mouvement invalide ! Case deja prise, piece en dehors du jeu ou format invalide.  /!\\\n\tEssayez un autre placement.\n\n\n";
	
	// Placement test to check if the logic of the game is correct
	printf("Coup tenté: Joueur : CERCLE, x : 2, y : 2 \n");
	if (Board_putPiece(2, 2, CIRCLE)!=PIECE_IN_PLACE){
		printf("%s\n", error_message);
	}
	printf("Coup tenté: Joueur : CROIX, x : 0, y : 0 \n");
	if (Board_putPiece(0, 0, CROSS)!=PIECE_IN_PLACE){
		printf("%s\n", error_message);
	}
	printf("Coup tenté: Joueur : CERCLE, x : 0, y : 0 \n");
	if (Board_putPiece(0, 0, CIRCLE)!=PIECE_IN_PLACE){
		printf("%s\n", error_message);
	}
	printf("Coup tenté: Joueur : CERCLE, x : 0, y : 2 \n");
	if (Board_putPiece(0, 2, CIRCLE)!=PIECE_IN_PLACE){
		printf("%s\n", error_message);
	}
	printf("Coup tenté: Joueur : CROIX, x : 1, y : 0 \n");
	if (Board_putPiece(1, 0, CROSS)!=PIECE_IN_PLACE){
		printf("%s\n", error_message);
	}
	printf("Coup tenté: Joueur : CERCLE, x : 1, y : 1 \n");
	if (Board_putPiece(1, 1, CIRCLE)!=PIECE_IN_PLACE){	
		printf("%s\n", error_message);
	}
	printf("Coup tenté: Joueur : CROIX, x : 2, y : 0 \n");
	if (Board_putPiece(2, 0, CROSS)!=PIECE_IN_PLACE){	
		printf("%s\n", error_message);
	}
}

#endif //  #if defined CONFIG_PLAYER_MANAGER_MOCK
