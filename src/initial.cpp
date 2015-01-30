//initial.cpp

#include "primer.h"
#include "initial.h"
#include "sdl.h"
#include <SDL2/SDL.h>
#include <iostream>


void initialIndexes(indexStruct &indexArray){				//Initializes inital board
	int index = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int square = A1;
	int square64 = 0; 
	for( index = 0; index < SQNUM; index++)		//Sets all squares to -1
	{
		indexArray.sq120[index] = -1;
	}
	for( index = 0; index < 64; index++)
	{
		indexArray.sq64[index] = -1;
	}


	for( rank = RANK_1; rank <= RANK_8; rank++)	//Sets inner board values
	{
		for( file = FILE_A; file <= FILE_H; file++)
		{
			square = FR2SQ(file,rank);
			indexArray.sq120[square] = square64;
			indexArray.sq64[square64] = square;
			square64++;
		}
	}

	
}

void initialBoard(boardStruct &board)
{
	int file = FILE_A;
	int rank = RANK_8;
	int square64 = 0;
	int square120 = 0;
	int piece = 0;
	board.side = WHITE;
	//Initialize starting board set
	int index = 0;
	int count = 0;
	for( index = 0; index < 64; index++)
	{
		board.sq64[index] = -1;
	}
	for( index = 0; index < SQNUM; index++)
	{
		board.sq120[index] = -1;
	}
	
	board.sq64[0]  = wqR;
	board.sq64[1]  = wqN;
	board.sq64[2]  = wqB;
	board.sq64[3]  = wQ;
	board.sq64[4]  = wK;
	board.sq64[5]  = wkB;
	board.sq64[6]  = wkN;
	board.sq64[7]  = wkR;
	board.sq64[56] = bqR; 
	board.sq64[57] = bqN;
	board.sq64[58] = bqB;
	board.sq64[59] = bQ;
	board.sq64[60] = bK;
	board.sq64[61] = bkB;
	board.sq64[62] = bkN;
	board.sq64[63] = bkR; 
	
	index = 8;
	for( count = wPa; count <= wPh; count++ )
	{
		board.sq64[index] = count;
		index++;
	}

	index = 48;

	for( count = bPa; count <= bPh; count++ )
	{
		board.sq64[index] = count;
		index++;
	}
	
	for( index = 16; index <= 47; index++ )
	{
		board.sq64[index] = 0;
	}	

	for( rank = RANK_8; rank >= RANK_1; rank--)
	{
		for( file = FILE_A; file <= FILE_H; file++)
		{
			square64 = FR2SQ64(file, rank);
			square120 = FR2SQ(file , rank);
			piece = board.sq64[square64];
			board.sq120[square120] = piece;
		}
	}
}

void initialPieces(pieceStruct pieces[], boardStruct &board)
{
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
			piece = board.sq64[square64];
			if( piece != 0 )
			{
				pieces[piece].position = square;
				pieces[piece].bitboard = 0;
				pieces[piece].bitboard++;
				pieces[piece].bitboard <<= square64;
				if( piece >= wqR && piece <= wPh )
					pieces[piece].color = WHITE;
				if( piece >= bqR && piece <= bPh )
					pieces[piece].color = BLACK;
				if( (piece == wqR || piece == wkR) || (piece == bqR || piece == bkR) )
					pieces[piece].type = ROOK;			
				if( (piece == wqN || piece == wkN) || (piece == bqN || piece == bkN) )
					pieces[piece].type = KNIGHT;
				if( (piece == wqB || piece == wkB) || (piece == bqB || piece == bkB) )
					pieces[piece].type = BISHOP;
				if( (piece == wQ || piece == bQ) )
					pieces[piece].type = QUEEN;
				if( (piece == wK || piece == bK) )
					pieces[piece].type = KING;
				if( (piece >= wPa && piece <= wPh) || (piece >= bPa && piece <= bPh) )
					pieces[piece].type = PAWN;
			}
		}
	}
}

void initialBitboards(bitboardStruct &bb, pieceStruct pieces[])			//Hopefully initializes bitboards 
{
	//Initialize all bitboards (figure out attacking bitboards and put in pieceStruct)
	//Clear bitsets by setting to 0 then filling with data from piecelist
	bb.whiteRooks = 0;
	bb.whiteRooks = ( pieces[wqR].bitboard | pieces[wkR].bitboard );

	bb.whiteKnights = 0;
	bb.whiteKnights = ( pieces[wqN].bitboard | pieces[wkN].bitboard );

	bb.whiteBishops = 0;
	bb.whiteBishops = ( pieces[wqB].bitboard | pieces[wkB].bitboard );
	
	bb.whiteQueen = 0;
	bb.whiteQueen = ( pieces[wQ].bitboard );
	
	bb.whiteKing = 0;
	bb.whiteKing = ( pieces[wK].bitboard );
	
	bb.whitePawns = 0;
	bb.whitePawns =	pieces[wPa].bitboard    |
			pieces[wPb].bitboard    |
			pieces[wPc].bitboard    |
			pieces[wPd].bitboard    |
			pieces[wPe].bitboard    |
			pieces[wPf].bitboard    |
			pieces[wPg].bitboard    |
			pieces[wPh].bitboard;

	bb.whitePieces = 
			bb.whiteRooks   |
			bb.whiteKnights |
			bb.whiteBishops |
			bb.whiteQueen   | 	
			bb.whiteKing    |
			bb.whitePawns;  
	 
	bb.blackRooks = 0;
	bb.blackRooks = ( pieces[bqR].bitboard | pieces[bkR].bitboard );

	bb.blackKnights = 0;
	bb.blackKnights = ( pieces[bqN].bitboard | pieces[bkN].bitboard );

	bb.blackBishops = 0;
	bb.blackBishops = ( pieces[bqB].bitboard | pieces[bkB].bitboard );
	
	bb.blackQueen = 0;
	bb.blackQueen = ( pieces[bQ].bitboard );
	
	bb.blackKing = 0;
	bb.blackKing = ( pieces[bK].bitboard );
	
	bb.blackPawns = 0;
	bb.blackPawns =	pieces[bPa].bitboard    |
			pieces[bPb].bitboard    |
			pieces[bPc].bitboard    |
			pieces[bPd].bitboard    |
			pieces[bPe].bitboard    |
			pieces[bPf].bitboard    |
			pieces[bPg].bitboard    |
			pieces[bPh].bitboard;

	bb.blackPieces =
		 	bb.blackRooks   |
			bb.blackKnights |
			bb.blackBishops |
			bb.blackQueen   | 	
			bb.blackKing    |
			bb.blackPawns;  
	 
	bb.occupiedSquares = bb.blackPieces | bb.whitePieces;
	bb.emptySquares = ~bb.occupiedSquares;
	
}
/*
int initialSDL()
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Collider 0.01", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	if(window == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == nullptr){
		SDL_DestroyWindow(window);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_Delay(60000);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
*/
void initializeAll(boardStruct &board, pieceStruct pieces[], indexStruct &indexArray, bitboardStruct &bb )
{
	initialIndexes(indexArray);
	initialBoard(board);
	initialPieces(pieces, board);
	initialBitboards(bb, pieces);
//	initialSDL();
}
