//initial.cpp

#include "primer.h"
#include "initial.h"
#include "sdl.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "board.h"
#include <vector>

/* Global variables created in initialization */
boardStruct board;
pieceStruct pce[33];
indexStruct indexA;  
bitboardStruct bb;
std::vector<undoStruct> undo;
bool stop;
bool flipFlag = false;
bool slowFlag = false;
bool genFlag = false;
int ply = 0;

//FII
/* Initialize index board */
void initialIndexes(){				
	int file, rank, square, square64, index;

	//sq120
	for( index = 0; index < SQNUM; index++){        //Sets all squares to -1
		indexA.sq[index] = -1;
		life++;
	}

	//sq64
	for( index = 0; index < 64; index++){
		indexA.sq64[index] = -1;
		life++;
	}

	square64 = 0;
	//Set inner board values
	for( rank = RANK_1; rank <= RANK_8; rank++){ 
		for( file = FILE_A; file <= FILE_H; file++){
			square = FR2SQ(file,rank);
			indexA.sq[square] = square64;
			indexA.sq64[square64] = square;
			square64++;
			life++;
		}
	}
}

//Initialize actual chess board
void initialBoard(){
	int file, rank, square64, square120, piece, index, count;
	board.side = WHITE;

	//Initialize starting board sets to -1
	for( index = 0; index < 64; index++){	//Will end up deleting board64
		board.sq64[index] = -1;
		life++;
	}
	
	//Actual board120 used in most files
	for( index = 0; index < SQNUM; index++){
		board.sq[index] = -1;
		life++;
	}
	
	//Hardcoding starting positions, will change when FEN parsing is added
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
	for( count = wPa; count <= wPh; count++ ){   //Fills in initial white pawns
		board.sq64[index] = count;
		index++;
		life++;
	}

	index = 48;
	for( count = bPa; count <= bPh; count++ ){   //Fills in initial black pawns
		board.sq64[index] = count;
		index++;
		life++;
	}
	
	for( index = 16; index <= 47; index++ ){    //Fills in initial empty squares
		board.sq64[index] = EMPTY;
		life++;
	}	

	for( rank = RANK_8; rank >= RANK_1; rank--){  //Fills in 120 from 64
		for( file = FILE_A; file <= FILE_H; file++){
			square64 = FR2SQ64(file,rank);
			square120 = FR2SQ(file,rank);
			piece = board.sq64[square64];
			board.sq[square120] = piece;
			life++;
		}
	}
}

/* Initialize piecelist from board */
void initialPieces(){
	int piece, rank, file, square64, square;

	for( rank = RANK_8; rank >= RANK_1; rank--){  //Fills piecelist from board
		for( file = FILE_A; file <= FILE_H; file++){
			square = FR2SQ( file,rank );
			square64 = FR2SQ64(file,rank);
			piece = getPiece(square);
			life++;

			if( piece != EMPTY ){
				pce[piece].pos = square;
				pce[piece].bitboard = EMPTY;
				pce[piece].bitboard++;
				pce[piece].bitboard <<= square64;
				pce[piece].color = getColor(square);
				pce[piece].type  = getType(square);
				pce[piece].value = getValue(square);
				pce[piece].life = true;
			}
			else if( piece == EMPTY ){
				pce[piece].color = NONE;	
				pce[piece].type = NOTYPE;
			}
		}
	}
}

/* Initialize Bitboards
   (unused at the moment) */
void initialBitboards(){ 

	//Initialize all bitboards
	//(figure out attacking bitboards and put in pieceStruct)
	//Clear bitsets by setting to 0 then filling with data from piecelist
	bb.whiteRooks = 0;
	bb.whiteRooks = ( pce[wqR].bitboard | pce[wkR].bitboard );

	bb.whiteKnights = 0;
	bb.whiteKnights = ( pce[wqN].bitboard | pce[wkN].bitboard );

	bb.whiteBishops = 0;
	bb.whiteBishops = ( pce[wqB].bitboard | pce[wkB].bitboard );
	
	bb.whiteQueen = 0;
	bb.whiteQueen = ( pce[wQ].bitboard );
	
	bb.whiteKing = 0;
	bb.whiteKing = ( pce[wK].bitboard );
	
	bb.whitePawns = 0;
	bb.whitePawns =	pce[wPa].bitboard    |
			pce[wPb].bitboard    |
			pce[wPc].bitboard    |
			pce[wPd].bitboard    |
			pce[wPe].bitboard    |
			pce[wPf].bitboard    |
			pce[wPg].bitboard    |
			pce[wPh].bitboard;

	bb.whitePieces = 
			bb.whiteRooks   |
			bb.whiteKnights |
			bb.whiteBishops |
			bb.whiteQueen   | 	
			bb.whiteKing    |
			bb.whitePawns;  
	 
	bb.blackRooks = 0;
	bb.blackRooks = ( pce[bqR].bitboard | pce[bkR].bitboard );

	bb.blackKnights = 0;
	bb.blackKnights = ( pce[bqN].bitboard | pce[bkN].bitboard );

	bb.blackBishops = 0;
	bb.blackBishops = ( pce[bqB].bitboard | pce[bkB].bitboard );
	
	bb.blackQueen = 0;
	bb.blackQueen = ( pce[bQ].bitboard );
	
	bb.blackKing = 0;
	bb.blackKing = ( pce[bK].bitboard );
	
	bb.blackPawns = 0;
	bb.blackPawns =	pce[bPa].bitboard    |
			pce[bPb].bitboard    |
			pce[bPc].bitboard    |
			pce[bPd].bitboard    |
			pce[bPe].bitboard    |
			pce[bPf].bitboard    |
			pce[bPg].bitboard    |
			pce[bPh].bitboard;

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
	
	bb.oppPawn = 0;
	bb.ownPieces = 0;	
	bb.file[FILE_H] = 0x8080808080808080;
	bb.file[FILE_G] = 0x4040404040404040;
	bb.file[FILE_F] = 0x2020202020202020;
	bb.file[FILE_E] = 0x1010101010101010;
	bb.file[FILE_D] = 0x808080808080808;
	bb.file[FILE_C] = 0x404040404040404;
	bb.file[FILE_B] = 0x202020202020202;
	bb.file[FILE_A] = 0x101010101010101;

	bb.rank[RANK_1] = 0xFF;
	bb.rank[RANK_2] = 0xFF00;
	bb.rank[RANK_3] = 0xFF0000;
	bb.rank[RANK_4] = 0xFF000000;
	bb.rank[RANK_5] = 0xFF00000000;
	bb.rank[RANK_6] = 0xFF0000000000;
	bb.rank[RANK_7] = 0xFF000000000000;
	bb.rank[RANK_8] = 0xFF00000000000000;
}

/* Initialize movelists */
void initializeMoveLists(){
}
/* Ran first in main to initialize everything */
void initializeAll(){
	initialIndexes();
	initialBoard();
	initialPieces();
	initialBitboards();
	initSDL();
	life++;
}
