#include "board.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 3

void (*SquareChangeCallback_ptr) (Coordinate x, Coordinate y, PieceType newContent) = NULL;
void (*EndOfGameCallback_ptr) (GameResult result) = NULL;

// DataTest Board for 
PieceType board[BOARD_SIZE][BOARD_SIZE];
/**
 * Check if the game has to be ended. Only alignment from the last
 * modified square are checked.
 *
 * @param [in] boardSquares the board to check
 * @param [in] lastChangeX the colum where the last piece has been put
 * @param [in] lastChangeY the row where the last piece has been put
 * @param [out] gameResult the winning status if the game has ended (value is not set if
 * the game is not finished)
 *
 * @pre lastChangeX must be in [0..2]
 * @pre lastChangeY must be in [0..2]
 * @pre gameResult must point on an allocated GameResult variable
 *
 * @return a boolean that tells if the game is finished
 */
static bool isGameFinished (const PieceType boardSquares[3][3], Coordinate lastChangeX, Coordinate lastChangeY, GameResult *gameResult)
{
	// check wether the last piece placed is inside the board or not and raise an error if not
	assert((lastChangeX >= 0 && lastChangeX<=2) && (lastChangeY >= 0 && lastChangeY<=2));

  	// Test 1st win condition rows
	for (Coordinate i = 0; i < 3; ++i)
	{
		// if on the given row we have only one type of pieces, then we have a winner
		if (boardSquares[i][0] != NONE && boardSquares[i][0] == boardSquares[i][1] && boardSquares[i][1] == boardSquares[i][2])
		{
			// then we check what piece is on one square of the given row and assign the corresponding value to gameResult
      		if (boardSquares[i][0] == CROSS) {
        		*gameResult = CROSS_WINS;
      		} else {
        		*gameResult = CIRCLE_WINS;
      		}
			return true;
		}
	}

	// Test 2nd win condition : columns
	for (Coordinate i = 0; i < 3; ++i)
	{
		// if on the given row we have only one type of pieces, then we have a winner
		if (boardSquares[0][i] != NONE && boardSquares[0][i] == boardSquares[1][i] && boardSquares[1][i] == boardSquares[2][i])
		{
			// then we check what pieces is on one square of the given column and assign the corresponding value to gameResult
      		if (boardSquares[0][i] == CROSS){
        		*gameResult = CROSS_WINS;
      		} else {
        		*gameResult = CIRCLE_WINS;
      		}
			return true;
		}
	}

	// Test 3rd win condition : diagonals, 2 diagonals only so we check them one by one
	// 1st diagonal 
	if (boardSquares[0][0] != NONE && boardSquares[0][0] == boardSquares[1][1] && boardSquares[1][1] == boardSquares[2][2])
	{
		// then we check what pieces is on one square of the diagonal and assign the corresponding value to gameResult
    	if (boardSquares[0][0] == CROSS){
      		*gameResult = CROSS_WINS;
    	} else {
      		*gameResult = CIRCLE_WINS;
    	}
		return true;
	}

	// 2nd diagonal 
	if (boardSquares[2][0] != NONE && boardSquares[2][0] == boardSquares[1][1] && boardSquares[1][1] == boardSquares[0][2])
	{	
		// then we check who is the player on the diagonal and assign the corresponding value to gameResult
    	if (boardSquares[2][0] == CROSS){
      		*gameResult = CROSS_WINS;
    	} else {
      		*gameResult = CIRCLE_WINS;
    	}
		return true; // we have a winner so the game is finished
	}

	// Tried this to check if we have a winner on each diagonals in one time but failed because we don't check the [0][0] [1][1] [2][2] one so it would result in a long if statement 
	// for (Coordinate x = 0; x <= 2; x++){
	// 	for (Coordinate y = 2; y <= 0; y++){
	// 		printf("Coordinate x: %d, y: %d\n", x, y);
	// 		if (boardSquares[1][1] != NONE && boardSquares[1][1] == boardSquares[x][y] && boardSquares[1][1] == boardSquares[y][x]){
	// 			if (boardSquares[1][1] == CROSS){
    //   				*gameResult = CROSS_WINS;
    // 			} else {
    //   				*gameResult = CIRCLE_WINS;
    // 			}
	// 			return true; // we have a winner so the game is finished
	// 		}
	// 	}
	// }

	// Test draw condition
	// if all the previous conditions weren't true, then we check each square to see if there are still NONE squares on the board
	for (Coordinate x = 0; x < 3; ++x)
	{
		for (Coordinate y = 0; y < 3; ++y)
		{
			// if there are still NONE squares on the board then the game is not finished
			if (boardSquares[x][y] == NONE)
			{
				return false;
			}
		}
	}
	// either way if we get here that means all the squares on the board are taken and we have no winner so it's a DRAW
	*gameResult = DRAW;
	return true;
}

void Board_init (SquareChangeCallback onSquareChange, EndOfGameCallback onEndOfGame)
{
	for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
          board[i][j] = NONE;
    	}
  	}
  	// Initialize the board state
	SquareChangeCallback_ptr = onSquareChange;
	EndOfGameCallback_ptr = onEndOfGame;
}

void Board_free ()
{
  	// Reset the callback functions
  	SquareChangeCallback_ptr = NULL;
  	EndOfGameCallback_ptr = NULL;
}

PutPieceResult Board_putPiece (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
  	// Check if the placement is valid else we return SQUARE_IS_NOT_EMPTY
	if ((x < 0 || x > 2) || (y < 0 || y > 2) || kindOfPiece == NONE){
		return SQUARE_IS_NOT_EMPTY;
	}

  	// Check if the square is empty
  	if (Board_getSquareContent(x, y) != NONE){
		return SQUARE_IS_NOT_EMPTY;
	}

	else{
		//Place the piece on the board
		board[x][y] = kindOfPiece;
	}

	GameResult gameResult;

	// Notify the square change to the rest of the program
  	if (SquareChangeCallback_ptr != NULL)
  	{
		SquareChangeCallback_ptr(x, y, kindOfPiece);
  	}

  	// Check if the game is finished
  	if (isGameFinished(board, x, y, &gameResult))
  	{
    	// Notify the end of game to the rest of the program
    	if (EndOfGameCallback_ptr != NULL)
    	{
     		EndOfGameCallback_ptr(gameResult);
    	}
  	}
  	return PIECE_IN_PLACE;
}

PieceType Board_getSquareContent (Coordinate x, Coordinate y)
{
	return board[x][y];
}
