/**
 * @file board_view_text.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "board_view.h"
#include "board.h"
#include "game.h"
#include "player_manager_sdl.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "tictactoe_errors.h"

#ifndef CONFIG_SDLUI
#define CONFIG_SDLUI

#define HEIGHT 480
#define WIDTH 480 
#define SIZE_FONT 35
#define BOARD_SIZE 3
#define PIXEL_SIZE 153
#define BUTTON_WIDTH 300
#define REPLAY_BUTTON_HEIGHT 80
#define QUIT_BUTTON_HEIGHT 84

static SDL_Window *MainWindow = NULL;
static SDL_Renderer *MainRenderer = NULL;
static SDL_Surface *BackgroundImage = NULL;
static SDL_Surface *SpriteO = NULL;
static SDL_Surface *SpriteX = NULL;
static SDL_Surface *quit_button = NULL;
static SDL_Surface *replay_button = NULL;
static SDL_Surface *cannotPlaceMessage = NULL;
static SDL_Surface *PlayerTurnMessage = NULL;
static SDL_Surface *endOfGameMessage = NULL;
static Mix_Chunk *winning_sound = NULL;
static Mix_Chunk *placed_piece_sound = NULL;
static Mix_Chunk *draw_sound = NULL;
static Mix_Chunk *wrong_placement_sound = NULL;
static Mix_Chunk *starting_game_sound = NULL;
SDL_Color YELLOW = {209, 181, 0};
static TTF_Font *TicTacToe = NULL;

PieceType board[BOARD_SIZE][BOARD_SIZE];

static void renderImage (SDL_Surface *image, int x, int y)
{
	SDL_Texture *aTexture;
	aTexture = SDL_CreateTextureFromSurface(MainRenderer, image);
	assert (aTexture != NULL);
	SDL_Rect pos = {x, y, image->w, image->h};
	SDL_RenderCopy(MainRenderer, aTexture, 0, &pos);
	SDL_DestroyTexture(aTexture);
}

void BoardView_init (void)
{
	// Initialize SDL
	int result = SDL_Init (SDL_INIT_VIDEO);
	if (result != 0)
	{
		fatalError (SDL_GetError ());
	}
	atexit (SDL_Quit);

	// Creates the window
	MainWindow = SDL_CreateWindow ("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 480, 0);
	if (MainWindow == NULL)
	{
		fatalError (SDL_GetError ());
	}

	// Creates the main renderer
	MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (MainRenderer == NULL)
	{
		fatalError(SDL_GetError());
	}

	// Initialize SDL_image
	int initted=IMG_Init(IMG_INIT_PNG);
	if (initted != IMG_INIT_PNG)
	{
		fatalError(IMG_GetError());
	}

	if (TTF_Init() == -1){
		fatalError(TTF_GetError());
	}

	//Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        fatalError(Mix_GetError());   
    }
	// Loads images
	BackgroundImage = IMG_Load("../etape3/background.png");
	if (BackgroundImage == NULL){
		fatalError(IMG_GetError());
	}
	SpriteO = IMG_Load("../etape3/sprite_O.png");
	if (SpriteO == NULL){
		fatalError(IMG_GetError());
	}
	SpriteX = IMG_Load("../etape3/sprite_X.png");
	if (SpriteX == NULL){
		fatalError(IMG_GetError());
	}
	replay_button = IMG_Load("../etape3/replay_button.png");
	if (replay_button == NULL){
		fatalError(IMG_GetError());
	}

	quit_button = IMG_Load("../etape3/quit_button.png");
	if (quit_button == NULL){
		fatalError(IMG_GetError());
	}

	// Creates the font
	TicTacToe = TTF_OpenFont("../etape3/Purple_Smile.ttf", SIZE_FONT);
	if (TicTacToe == NULL){
		fatalError(TTF_GetError());
	}

	// Load the sound effects
	winning_sound = Mix_LoadWAV("../etape3/wow_winning_sound.wav");
	draw_sound = Mix_LoadWAV("../etape3/aww_draw_sound.wav");
	wrong_placement_sound = Mix_LoadWAV("../etape3/wrong_placement_sound.wav");
	placed_piece_sound = Mix_LoadWAV("../etape3/piece_in_place_sound.wav");
	starting_game_sound = Mix_LoadWAV("../etape3/starting_game_sound.wav");
	Mix_PlayChannel( -1, starting_game_sound, 0 );
}

void BoardView_free (void)
{
	SDL_DestroyRenderer(MainRenderer);
	SDL_DestroyWindow(MainWindow);
	SDL_FreeSurface(SpriteX);
	SDL_FreeSurface(SpriteO);
	SDL_FreeSurface(BackgroundImage);
	SDL_FreeSurface(cannotPlaceMessage);
	SDL_FreeSurface(PlayerTurnMessage);
	Mix_FreeChunk(winning_sound);
	Mix_FreeChunk(wrong_placement_sound);
	Mix_FreeChunk(starting_game_sound);
	Mix_FreeChunk(placed_piece_sound);
	Mix_FreeChunk(draw_sound);
	TTF_CloseFont(TicTacToe);
	Mix_CloseAudio();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void BoardView_displayAll (void)
{
	SDL_RenderClear(MainRenderer);
    renderImage(BackgroundImage, 0, 0);
	for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == CROSS) {
                renderImage(SpriteX, i * PIXEL_SIZE, j * PIXEL_SIZE);
            } else if (board[i][j] == CIRCLE) {
                renderImage(SpriteO, i * PIXEL_SIZE, j * PIXEL_SIZE);
            }
        }
    }
	SDL_RenderPresent(MainRenderer);	
}

void BoardView_displaySquare (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
	switch(kindOfPiece){
		case CROSS:
			board[x][y] = CROSS;
			break;
		case CIRCLE:
			board[x][y] = CIRCLE;
			break;
		case NONE:
			board[x][y] = NONE;
			break;
		default:
			break;
	}
	BoardView_displayAll();
}

void BoardView_displayEndOfGame (GameResult result)
{
	char * endOfGameText;
	int x = 0;
	switch (result){
    	case CROSS_WINS:
			endOfGameText = "Bravo joueur CROIX !";
			x = 40;
			break;
    	case CIRCLE_WINS: 
			endOfGameText = "Bravo joueur CERCLE !";
			x = 40;
			break;
    	case DRAW: 
			endOfGameText = "Match Nul !";
			x = 140;
			break;
    	default: 
			exit(1);
			break;
  	}
	endOfGameMessage = TTF_RenderText_Solid(TicTacToe, endOfGameText, YELLOW);
	if (endOfGameMessage == NULL){
		printf("Error :%s\n", TTF_GetError());
	}

    if (x == 140){
		Mix_PlayChannel( -1, draw_sound, 0 ); 
	}
	else {
		Mix_PlayChannel( -1, winning_sound, 0 );
	}
	// Affiche le plateau final pendant 2 secondes
	SDL_Delay (2000);
	// Puis affiche le message de fin sur le fond d'écran du plateau sans les pièces
	renderImage(BackgroundImage, 0, 0);
	renderImage(endOfGameMessage, x, HEIGHT/2-SIZE_FONT/2);
	SDL_RenderPresent(MainRenderer);
	SDL_Delay (3000);
	SDL_FreeSurface(endOfGameMessage);

	if (replayGame() == true) {
		Game_free();
		Game_init();
		Game_loop();
	}
	else {
		Game_free();
		exit(1);
	}
}

void BoardView_displayPlayersTurn (PieceType thisPlayer)
{
	SDL_RenderClear(MainRenderer);
	const char cross_player_turn[30]= "A vous joueur croix!";
	const char circle_player_turn[30]= "A vous joueur cercle!";
	switch (thisPlayer){
    case CROSS : 
		PlayerTurnMessage = TTF_RenderText_Solid(TicTacToe, cross_player_turn, YELLOW); 
		break;
    case CIRCLE : 
		PlayerTurnMessage = TTF_RenderText_Solid(TicTacToe, circle_player_turn, YELLOW);
		break;
    default : 
		break;
  }
  renderImage(BackgroundImage, 0, 0);
  renderImage(PlayerTurnMessage, 30, HEIGHT/2-SIZE_FONT/2);
  SDL_RenderPresent(MainRenderer);
  SDL_Delay(1000);
  BoardView_displayAll();
}

bool replayGame(void){
	SDL_Event event;
	bool replayClicked = false;
	bool clickDetected = false;
	int x_mouse, y_mouse;
	int x_pos, y_pos;
	x_pos = (WIDTH - BUTTON_WIDTH) / 2;
	y_pos = (HEIGHT - REPLAY_BUTTON_HEIGHT - QUIT_BUTTON_HEIGHT - PIXEL_SIZE - 20) / 2;

	SDL_RenderClear(MainRenderer);
	renderImage(BackgroundImage, 0, 0);
	renderImage(quit_button, x_pos, y_pos + QUIT_BUTTON_HEIGHT + PIXEL_SIZE + 20);
	renderImage(replay_button, x_pos, y_pos);
	SDL_RenderPresent(MainRenderer);

	while ( clickDetected == false ){
		SDL_WaitEvent(&event);
		switch ( event.type ){
			case SDL_QUIT:
				exit(1);
				break;
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&x_mouse, &y_mouse);
				if ( ( (x_mouse >= x_pos) && (x_mouse <= x_pos + BUTTON_WIDTH) ) && ( (y_mouse >= y_pos) && (y_mouse <= y_pos + REPLAY_BUTTON_HEIGHT) ) ) {
					replayClicked = true;
					clickDetected = true;
				}
				else if ( ( (x_mouse >= x_pos) && (x_mouse <= x_pos + BUTTON_WIDTH) ) && ( (y_mouse >= y_pos + QUIT_BUTTON_HEIGHT + PIXEL_SIZE + 20) && (y_mouse <= y_pos + QUIT_BUTTON_HEIGHT + PIXEL_SIZE + 20 + QUIT_BUTTON_HEIGHT) ) ) {
					replayClicked = false;
					clickDetected = true;
				}
				else if ( (x_mouse >= 0 && x_mouse <= WIDTH) && (y_mouse >= 0 && y_mouse <= HEIGHT) ) {
                    // click was inside the window but not on either button
                }
		}
	}
	return replayClicked;
}

void BoardView_sayCannotPutPiece (void)
{
	SDL_RenderClear(MainRenderer);
	const char cannotPlaceText[17] = "Case deja prise!";
	cannotPlaceMessage = TTF_RenderText_Solid(TicTacToe, cannotPlaceText, YELLOW);
	if (cannotPlaceMessage == NULL){
		printf("Error :%s\n", TTF_GetError());
	}
	// Affiche le message d'erreur pendant 1 sec sur le fond d'ecran sans les pieces puis réaffiche les pieces
	Mix_PlayChannel( -1, wrong_placement_sound, 0 );
	renderImage(BackgroundImage, 0, 0);
	renderImage(cannotPlaceMessage, 100, HEIGHT/2-SIZE_FONT/2);
	SDL_RenderPresent(MainRenderer);
	SDL_Delay(1000);
	BoardView_displayAll();
}

#endif // defined CONFIG_SDLUI
