//sdl.cpp

#include <primer.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "sdl.h"
#include <SDL2_image/SDL_image.h>

/* Global SDL Variables */

//The rendering window
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gImage = NULL;
SDL_Surface* gWhitePawn = NULL;
SDL_Surface* gWhiteKnight = NULL;
SDL_Surface* gWhiteBishop = NULL;
SDL_Surface* gWhiteRook = NULL;
SDL_Surface* gWhiteQueen = NULL;
SDL_Surface* gWhiteKing = NULL;
SDL_Surface* gBlackPawn = NULL;
SDL_Surface* gBlackKnight = NULL;
SDL_Surface* gBlackBishop = NULL;
SDL_Surface* gBlackRook = NULL;
SDL_Surface* gBlackQueen = NULL;
SDL_Surface* gBlackKing = NULL;

SDL_Surface* gWhiteSquare = NULL;
SDL_Surface* gBlackSquare = NULL;

//The renderer 
SDL_Renderer* gRenderer = NULL;

//Piece and square textures
SDL_Texture* pieceTextures[13];
SDL_Texture* squareTextures[3];


bool initSDL(){
	//Initialization flag
	bool success = true;

	if( SDL_Init(SDL_INIT_EVERYTHING) < 0){
			printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			success = false;
	}
	else{
		//Create Window
		gWindow = SDL_CreateWindow( "Collider 0.5", 1200, 0, SCREEN_WIDTH, SCREEN_HEIGHT, !SDL_WINDOW_INPUT_FOCUS );
		if( gWindow == NULL ){
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
/*
		else{
			//Get Window Surface
			gSurface = SDL_GetWindowSurface( gWindow );	
		}
*/
		//Create Renderer
		gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );	
		if( gRenderer == NULL ){
			printf( "Renderer could not be created! SDL_Error %s\n", SDL_GetError() );
			success = false;
		}
		else{
			//Initialize renderer color
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );		
	}

	loadMedia();
	createTextures();
	}	
	return success;
}

bool loadMedia(){
	//Loading success flag
	bool success = true;

	//Load splash image
	gImage = IMG_Load( "../res/whiteRook.bmp" );
	if( gImage == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "whiteRook.bmp", SDL_GetError() );
		success = false;
	}

	gWhitePawn = IMG_Load( "../res/whitePawn2.bmp" );
	if( gWhitePawn == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "whitePawn.bmp", SDL_GetError() );
		success = false;
	}
	
	gWhiteKnight = IMG_Load( "../res/whiteKnight.bmp" );
	if( gWhiteKnight == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "whiteKnight.bmp", SDL_GetError() );
		success = false;
	}
	gWhiteBishop = IMG_Load( "../res/whiteBishop.bmp" );
	if( gWhiteBishop == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "whiteBishop.bmp", SDL_GetError() );
		success = false;
	}
	gWhiteRook = IMG_Load( "../res/whiteRook.bmp" );
	if( gWhiteRook == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "whiteRook.bmp", SDL_GetError() );
		success = false;
	}
	gWhiteQueen = IMG_Load( "../res/whiteQueen.bmp" );
	if( gWhiteQueen == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "whiteQueen.bmp", SDL_GetError() );
		success = false;
	}
	gWhiteKing = IMG_Load( "../res/whiteKing.bmp" );
	if( gWhiteKing == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "whiteKing.bmp", SDL_GetError() );
		success = false;
	}
	gBlackPawn = IMG_Load( "../res/blackPawn2.bmp" );
	if( gBlackPawn == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "blackPawn.bmp", SDL_GetError() );
		success = false;
	}
	gBlackKnight = IMG_Load( "../res/blackKnight.bmp" );
	if( gBlackKnight == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "blackKnight.bmp", SDL_GetError() );
		success = false;
	}
	gBlackBishop = IMG_Load( "../res/blackBishop.bmp" );
	if( gBlackBishop == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "blackBishop.bmp", SDL_GetError() );
		success = false;
	}
	gBlackRook = IMG_Load( "../res/blackRook.bmp" );
	if( gBlackRook == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "blackRook.bmp", SDL_GetError() );
		success = false;
	}
	gBlackQueen = IMG_Load( "../res/blackQueen.bmp" );
	if( gBlackQueen == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "blackQueen.bmp", SDL_GetError() );
		success = false;
	}
	gBlackKing = IMG_Load( "../res/blackKing.bmp" );
	if( gBlackKing == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "blackKing.bmp", SDL_GetError() );
		success = false;
	}
	gWhiteSquare = IMG_Load( "../res/whiteSquare.bmp" );
	if( gWhiteSquare == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "whiteSquare.bmp", SDL_GetError() );
		success = false;
	}
	gBlackSquare = IMG_Load( "../res/blackSquare.bmp" );
	if( gBlackSquare == NULL ){
		printf( "Unable to load image %s! SDL_Error %s\n", "blackSquare.bmp", SDL_GetError() );
		success = false;
	}
	return success;
}

SDL_Texture* loadTexture( SDL_Surface* surface ){
	SDL_Texture* gTexture = NULL;

	gTexture = SDL_CreateTextureFromSurface( gRenderer, surface );
	if( gTexture == NULL )
		std::cout << "Unable to create SDL Texture!\n";

	SDL_FreeSurface( surface );

	return gTexture;
}
//Create all the textures from surfaces
void createTextures(){
	pieceTextures[1] = loadTexture( gWhitePawn );
	pieceTextures[2] = loadTexture( gWhiteKnight );
	pieceTextures[3] = loadTexture( gWhiteBishop );
	pieceTextures[4] = loadTexture( gWhiteRook );
	pieceTextures[5] = loadTexture( gWhiteQueen );
	pieceTextures[6] = loadTexture( gWhiteKing );
	pieceTextures[7] = loadTexture( gBlackPawn );
	pieceTextures[8] = loadTexture( gBlackKnight );
	pieceTextures[9] = loadTexture( gBlackBishop );
	pieceTextures[10] = loadTexture( gBlackRook );
	pieceTextures[11] = loadTexture( gBlackQueen );
	pieceTextures[12] = loadTexture( gBlackKing );
	
	squareTextures[WHITE] = loadTexture( gWhiteSquare );
	squareTextures[BLACK] = loadTexture( gBlackSquare );
}

void closeSDL(){
	//Deallocate surface
	SDL_FreeSurface( gImage );
	gImage = NULL;
	SDL_FreeSurface( gWhitePawn );
	gWhitePawn = NULL;
	SDL_FreeSurface( gWhiteKnight );
	gWhiteKnight = NULL;
	SDL_FreeSurface( gWhiteBishop );
	gWhiteBishop = NULL;
	SDL_FreeSurface( gWhiteQueen );
	gWhiteQueen = NULL;
	SDL_FreeSurface( gWhiteKing );
	gWhiteKing = NULL;
	SDL_FreeSurface( gBlackPawn );
	gBlackPawn = NULL;
	SDL_FreeSurface( gBlackKnight );
	gBlackKnight = NULL;
	SDL_FreeSurface( gBlackBishop );
	gBlackBishop = NULL;
	SDL_FreeSurface( gBlackQueen );
	gBlackQueen = NULL;
	SDL_FreeSurface( gBlackKing );
	gBlackKing = NULL;
	SDL_FreeSurface( gWhiteSquare );
	gWhiteSquare = NULL;
	SDL_FreeSurface( gBlackSquare );
	gBlackSquare = NULL;

	//DESTROY WINDOW
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//DESTROY RENDERER
	SDL_DestroyRenderer( gRenderer );
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}












