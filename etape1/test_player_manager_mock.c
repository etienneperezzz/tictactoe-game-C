/**
 * @file test_checkEndOfGame.c
 *
 * End of game check function test suite
 *
 * @date 27 oct. 2016
 * @author Jonathan ILIAS-PILLET
 */

// WARNING : ".c" file inclusion only allowed for unit tests !
#include "board.c"
#include "test_player_manager_mock.h"
#include <stdio.h>

typedef struct
{
	PieceType board[3][3];
	Coordinate lastPutX;
	Coordinate lastPutY;
    PieceType playerTurn;
	bool expectedEndOfGameResult;
	GameResult expectedGameResult;
    PutPieceResult expectedPutPieceResult;
} BoardDataTest;

static const BoardDataTest DataTest[] =

{

{

{

{NONE, NONE, NONE},

{NONE, NONE, NONE},

{NONE, NONE, NONE}}, 0, 0, CROSS, false, DRAW, PIECE_IN_PLACE},

{

{

{NONE, NONE, NONE},

{NONE, CROSS, NONE},

{NONE, NONE, NONE}}, 1, 1, CIRCLE, false, DRAW, SQUARE_IS_NOT_EMPTY},

{

{

{NONE, NONE, NONE},

{NONE, CIRCLE, NONE},

{NONE, NONE, NONE}}, 2, 2, CROSS, false, DRAW, SQUARE_IS_NOT_EMPTY},

{

{

{CROSS, NONE, NONE},

{CROSS, CIRCLE, NONE},

{NONE, NONE, NONE}}, 2, 0, CROSS, true, CROSS_WINS, PIECE_IN_PLACE},

{

{

{CROSS, NONE, NONE},

{CROSS, CIRCLE, CIRCLE},

{NONE, CROSS, NONE}}, 1, 2, CROSS, false, DRAW, SQUARE_IS_NOT_EMPTY},

{

{

{CROSS, NONE, NONE},

{CIRCLE, CIRCLE, NONE},

{NONE, NONE, CROSS}}, 2, 2, CIRCLE, false, DRAW, SQUARE_IS_NOT_EMPTY},

{

{

{CROSS, NONE, NONE},

{CROSS, CIRCLE, CIRCLE},

{CROSS, NONE, NONE}}, 0, 1, CIRCLE, true, CROSS_WINS, PIECE_IN_PLACE},

{

{

{CROSS, NONE, NONE},

{CIRCLE, CIRCLE, CIRCLE},

{CROSS, NONE, NONE}}, 2, 1, CROSS, true, CIRCLE_WINS, PIECE_IN_PLACE},

{

{

{CROSS, NONE, NONE},

{CIRCLE, CROSS, CIRCLE},

{NONE, NONE, CROSS}}, 0, 0, CIRCLE, true, CROSS_WINS, SQUARE_IS_NOT_EMPTY},

{

{

{CROSS, NONE, CIRCLE},

{CROSS, CIRCLE, NONE},

{CIRCLE, NONE, CROSS}}, 1, 1, NONE, true, CIRCLE_WINS, SQUARE_IS_NOT_EMPTY},

{

{

{CIRCLE, CROSS, CIRCLE},

{CIRCLE, CROSS, CIRCLE},

{CROSS, CIRCLE, CROSS}}, 2, 0, NONE, true, DRAW, SQUARE_IS_NOT_EMPTY}

};



void test_player_manager_mock(void)
{
	int successCount = 0;
	int failCount = 0;

	GameResult gameResult;
    PutPieceResult pieceResult;
	bool end;

	for (int i = 0; i < (sizeof(DataTest) / sizeof(BoardDataTest)); i++)
	{
        pieceResult = Board_putPiece(DataTest[i].lastPutX, DataTest[i].lastPutY, DataTest[i].playerTurn);
		end = isGameFinished (DataTest[i].board, DataTest[i].lastPutX, DataTest[i].lastPutY, &gameResult);
		if ((end != DataTest[i].expectedEndOfGameResult) && (pieceResult != DataTest[i].expectedPutPieceResult))
		{
			printf ("test #%d failed, expected end of game was %s\n", i,
					DataTest[i].expectedEndOfGameResult ? "true" : "false");
			failCount++;
		}
		else
		{
			successCount++;
		}
		if (end)
		{
			if (gameResult != DataTest[i].expectedGameResult)
			{
				printf ("test #%d failed, expected result of game was %s\n",	i,
						DataTest[i].expectedGameResult == CROSS_WINS ?
								"CROSS_WINS" :
						DataTest[i].expectedGameResult == CIRCLE_WINS ?
								"CIRCLE_WINS" : "DRAW");
				failCount++;
			}
			else
			{
				successCount++;
			}
		}
	}

	printf ("*********\n%d of %d test cases succeeded\n",
			successCount, successCount + failCount);
}


	