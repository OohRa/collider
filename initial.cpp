//initial.cpp


#include "primer.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#define RAND_64 ( 	(U64) rand() | \
			(U64) rand() << 15 | \
			(U64) rand() << 30 | \
			(U64) rand() << 45 | \
		       ((U64)rand() & 0xf << 60 )
int side = WHITE;
int fiftymove = 0;
int ply = 0;
int oppPly = 0;
int board64[64];
int board120[SQNUM];
int board120to64[SQNUM];
int board64to120[64];
pieceStruct pieceList[33];

//Global Bitboards

U64 whiteRooks;
U64 whiteKnights;
U64 whiteBishops;
U64 whiteQueen;
U64 whiteKing;
U64 whitePawns;
U64 whitePieces;

U64 blackRooks;
U64 blackKnights;
U64 blackBishops;
U64 blackQueen;
U64 blackKing;
U64 blackPawns;
U64 blackPieces;

U64 occupiedSquares;
U64 emptySquares; 

void initArray120to64()				//Initializes inital board
{
	int index = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int square = A1;
	int square64 = 0; 
	for( index = 0; index < SQNUM; index++)		//Sets all squares to -1
	{
		board120to64[index] = -1;
	}
	for( index = 0; index < 64; index++)
	{
		board64to120[index] = -1;
	}


	for( rank = RANK_1; rank <= RANK_8; rank++)	//Sets inner board values
	{
		for( file = FILE_A; file <= FILE_H; file++)
		{
			square = FR2SQ(file,rank);
			board120to64[square] = square64;
			board64to120[square64] = square;
			square64++;
		}
	}

	
}

void initialBoard()
{
	int side = WHITE;
	int fiftyMove = 0;
	int ply = 0;
	int oppPly = 0;	
	int file = FILE_A;
	int rank = RANK_8;
	int square64 = 0;
	int square120 = 0;
	int piece = 0;
	//Initialize starting board set
	int index = 0;
	int count = 0;
	for( index = 0; index < 64; index++)
	{
		board64[index] = -1;
	}
	for( index = 0; index < SQNUM; index++)
	{
		board120[index] = -1;
	}
	
	board64[0]  = wqR;
	board64[1]  = wqN;
	board64[2]  = wqB;
	board64[3]  = wQ;
	board64[4]  = wK;
	board64[5]  = wkB;
	board64[6]  = wkN;
	board64[7]  = wkR;
	board64[56] = bqR; 
	board64[57] = bqN;
	board64[58] = bqB;
	board64[59] = bQ;
	board64[60] = bK;
	board64[61] = bkB;
	board64[62] = bkN;
	board64[63] = bkR; 
	
	index = 8;
	for( count = wPa; count <= wPh; count++ )
	{
		board64[index] = count;
		index++;
	}

	index = 48;

	for( count = bPa; count <= bPh; count++ )
	{
		board64[index] = count;
		index++;
	}
	
	for( index = 16; index <= 47; index++ )
	{
		board64[index] = 0;
	}	

	for( rank = RANK_8; rank >= RANK_1; rank--)
	{
		for( file = FILE_A; file <= FILE_H; file++)
		{
			square64 = FR2SQ64(file, rank);
			square120 = FR2SQ(file , rank);
			piece = board64[square64];
			board120[square120] = piece;
		}
	}
}

void initialPieces()
{
	int index = 0;
	int count = 0;
	int pieceNum = 0;
	int piece = 0;
	int rank = 0;
	int file = 0;
	int square64 = 0;
	int square = 0;
	for( rank = RANK_8; rank >= RANK_1; rank--)
	{
		for( file = FILE_A; file <= FILE_H; file++)
		{
			square   = FR2SQ( file, rank );
			square64 = FR2SQ64(file, rank);
			piece = board64[square64];
			if( piece != 0 )
			{
				pieceList[piece].position = square;
				pieceList[piece].bitboard = 0;
				pieceList[piece].bitboard++;
				pieceList[piece].bitboard <<= square64;
				if( piece >= wqR && piece <= wPh )
					pieceList[piece].color = WHITE;
				if( piece >= bqR && piece <= bPh )
					pieceList[piece].color = BLACK;
				if( (piece == wqR || piece == wkR) || (piece == bqR || piece == bkR) )
					pieceList[piece].type = ROOK;			
				if( (piece == wqN || piece == wkN) || (piece == bqN || piece == bkN) )
					pieceList[piece].type = KNIGHT;
				if( (piece == wqB || piece == wkB) || (piece == bqB || piece == bkB) )
					pieceList[piece].type = BISHOP;
				if( (piece == wQ || piece == bQ) )
					pieceList[piece].type = QUEEN;
				if( (piece == wK || piece == bK) )
					pieceList[piece].type = KING;
				if( (piece >= wPa && piece <= wPh) || (piece >= bPa && piece <= bPh) )
					pieceList[piece].type = PAWN;
			}
		}
	}
}

void initialBitboards()			//Hopefully initializes bitboards 
{
	//Initialize all bitboards (figure out attacking bitboards and put in pieceStruct)
	//Clear bitsets by setting to 0 then filling with data from piecelist
	whiteRooks = 0;
	whiteRooks = ( pieceList[wqR].bitboard | pieceList[wkR].bitboard );

	whiteKnights = 0;
	whiteKnights = ( pieceList[wqN].bitboard | pieceList[wkN].bitboard );

	whiteBishops = 0;
	whiteBishops = ( pieceList[wqB].bitboard | pieceList[wkB].bitboard );
	
	whiteQueen = 0;
	whiteQueen = ( pieceList[wQ].bitboard );
	
	whiteKing = 0;
	whiteKing = ( pieceList[wK].bitboard );
	
	int index;
	whitePawns = 0;
	whitePawns =	pieceList[wPa].bitboard    |
			pieceList[wPb].bitboard    |
			pieceList[wPc].bitboard    |
			pieceList[wPd].bitboard    |
			pieceList[wPe].bitboard    |
			pieceList[wPf].bitboard    |
			pieceList[wPg].bitboard    |
			pieceList[wPh].bitboard;

	whitePieces = 	whiteRooks   |
			whiteKnights |
			whiteBishops |
			whiteQueen   | 	
			whiteKing    |
			whitePawns;  
	 
	blackRooks = 0;
	blackRooks = ( pieceList[bqR].bitboard | pieceList[bkR].bitboard );

	blackKnights = 0;
	blackKnights = ( pieceList[bqN].bitboard | pieceList[bkN].bitboard );

	blackBishops = 0;
	blackBishops = ( pieceList[bqB].bitboard | pieceList[bkB].bitboard );
	
	blackQueen = 0;
	blackQueen = ( pieceList[bQ].bitboard );
	
	blackKing = 0;
	blackKing = ( pieceList[bK].bitboard );
	
	blackPawns = 0;
	blackPawns =	pieceList[bPa].bitboard    |
			pieceList[bPb].bitboard    |
			pieceList[bPc].bitboard    |
			pieceList[bPd].bitboard    |
			pieceList[bPe].bitboard    |
			pieceList[bPf].bitboard    |
			pieceList[bPg].bitboard    |
			pieceList[bPh].bitboard;

	blackPieces = 	blackRooks   |
			blackKnights |
			blackBishops |
			blackQueen   | 	
			blackKing    |
			blackPawns;  
	 
	occupiedSquares = blackPieces | whitePieces;
	emptySquares = ~occupiedSquares;
	
}

int initialSDL()
{
	/* Initialize SDL Video and output error if error */
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	/* Create an SDL window! */
	SDL_Window *window = SDL_CreateWindow("Collider 0.01", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	if(window == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	/* Create a renderer */
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == nullptr){
		SDL_DestroyWindow(window);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_Delay(2000);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void initializeAll()
{
	initArray120to64();
	initialBoard();
	initialPieces();
	initialBitboards();
	initialSDL();
}

void nl(int lines)
{
	int lineCount = 0;
	for(lineCount = 0; lineCount < lines; lineCount++)
	{
		printf("\n");
	}
}

void stars(int stars)
{
	int starCount = 0;
	for( starCount = 0; starCount < stars; starCount++)
	{
		printf("*");
	}
}

void spaces(int spaces)
{
	int spaceCount = 0;
	for( spaceCount = 0; spaceCount < spaces; spaceCount++)
	{
		printf(" ");
	}
}
