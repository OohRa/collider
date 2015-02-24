//initial.cpp

#include "primer.h"
#include "initial.h"
#include "sdl.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "board.h"

boardStruct board;
pieceStruct pieces[33];
indexStruct indexArray;
bitboardStruct bb;
bool stop;

//FII
void initialIndexes(){				//Initializes inital board
	int file, rank, square, square64, index;

	for( index = 0; index < SQNUM; index++){		//Sets all squares to -1
		indexArray.sq[index] = -1;
		life++;
	}

	for( index = 0; index < 64; index++){
		indexArray.sq64[index] = -1;
		life++;
	}

	square64 = 0;
	for( rank = RANK_1; rank <= RANK_8; rank++){	//Sets inner board values
	
		for( file = FILE_A; file <= FILE_H; file++){
			square = FR2SQ(file,rank);
			indexArray.sq[square] = square64;
			indexArray.sq64[square64] = square;
			square64++;
			life++;
		}
	}
}

void initialBoard(){
	int file, rank, square64, square120, piece, index, count;
	board.side = WHITE;

	//Initialize starting board set
	for( index = 0; index < 64; index++){
		board.sq64[index] = -1;
		life++;
	}

	for( index = 0; index < SQNUM; index++){
		board.sq[index] = -1;
		life++;
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
	for( count = wPa; count <= wPh; count++ ){		//Fills in initial white pawns
		board.sq64[index] = count;
		index++;
		life++;
	}

	index = 48;
	for( count = bPa; count <= bPh; count++ ){		//Fills in initial black pawns
		board.sq64[index] = count;
		index++;
		life++;
	}
	
	for( index = 16; index <= 47; index++ ){		//Fills in initial empty squares
		board.sq64[index] = 0;
		life++;
	}	

	for( rank = RANK_8; rank >= RANK_1; rank--){		//Fills in 120 board from 64 board
		for( file = FILE_A; file <= FILE_H; file++){
			square64 = FR2SQ64(file, rank);
			square120 = FR2SQ(file, rank);
			piece = board.sq64[square64];
			board.sq[square120] = piece;
			life++;
		}
	}
}

/* Initialize piecelist from board */
void initialPieces(){

	int piece, rank, file, square64, square;

	for( rank = RANK_8; rank >= RANK_1; rank--){		//Fills piecelist from board64
		for( file = FILE_A; file <= FILE_H; file++){
			square = FR2SQ( file, rank );
			square64 = FR2SQ64(file, rank);
			piece = board.sq[square];
			life++;
			if( piece != 0 ){
				pieces[piece].pos = square;
				pieces[piece].bitboard = 0;
				pieces[piece].bitboard++;
				pieces[piece].bitboard <<= square64;
				pieces[piece].color = getColor(square);
				pieces[piece].type  = getType(square);
			}
			else if( piece == 0 ){
				pieces[piece].color = NONE;	
				pieces[piece].type = NOTYPE;
			}
		}
	}
}

void initialBitboards(){			//Hopefully initializes bitboards 

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
	life++;
	
}

void initializeAll(){
	initialIndexes();
	initialBoard();
	initialPieces();
	initialBitboards();
	initSDL();
	life++;
}
