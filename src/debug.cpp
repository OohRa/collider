//debug.cpp
//Use for writing functions to test 

#include <iostream>
#include "primer.h"
#include "debug.h"
#include "display.h"
#include "board.h"
#include "eval.h"

void boardDebug(){
	std::cout << "\nBoard Debug\n";
	for( int i = 120; i > 0; i-- ){
		if( board.sq[i] < 10 && board.sq[i] >= 0 )
			std::cout << " ";
		std::cout << board.sq[i] << " ";
		if( i % 10 == 0 ) 
			nl(1);
		
	}
	nl(1);
}



void bitboardDebug(){
	/* Displays bitboards for debugging */
	//Pieces
	for( int c = WHITE; c <= BLACK; ++c ){
		int piece = (c == WHITE) ? wqR: bqR;
		if( c == WHITE )
			std::cout << "White ";
		else
			std::cout << "Black ";
		std::cout << "Pieces\n";
		
		//General piece bb loop
		for( int i = piece; i <= piece + 15; ++i ){
			std::cout << (std::bitset<64>) pce[i].bitboard << std::endl;
		}
		
		//Pawns
		std::cout << "Pawns\n";
		bbDisp( bb.pawns[c]);
		std::cout << (std::bitset<64>) bb.pawns[c] << std::endl;
		//Rooks
		std::cout << "Rooks\n";
		std::cout << (std::bitset<64>) bb.rooks[c] << std::endl;
		//Pieces
		std::cout << "Pieces\n";
		std::cout << (std::bitset<64>) bb.pieces[c] << std::endl;
		
	}

	//All pieces
	std::cout << "Occupied Squares\n";
	std::cout << (std::bitset<64>) bb.occupiedSquares << std::endl;
	std::cout << "Empty Squares\n";
	std::cout << (std::bitset<64>) bb.emptySquares << std::endl;
/*
	//Passed Pawn bitboards
	std::cout << "Passed Pawn Boards\n";
	for(int i = WHITE; i <= BLACK; ++i ){
		for(int j = 0; j < 58; ++j ){
			dispSq( j + 31 );
			bbDisp( bb.passPwn[i][j] );
			std::cout << (std::bitset<64>) bb.passPwn[i][j] << "\n";
		}
	}
*/
	


	/* Reverses bitboard and displays */
/*     Reverse by 64 steps 	
	U64 bbReverse = 0;
	U64 garbage;
	U64 firstBit;
	
	garbage = whiteRooks;
	
	for( int index = 0; index < 63; index++ ){
		firstBit = ( garbage % 2 );
		if( firstBit == 1 )	
			bbReverse++;

		bbReverse <<= 1;
		garbage >>= 1;
	}

	nl(10);	
	std::cout << (std::bitset<64>) bbReverse << std::endl;
*/

	/* Reverse bitboard faster */
/*
	int lastBit = 0;
	int firstBit = 0;
	int bigMod = 0;
	int smallMod = 0;
	int bigExp = 63;
	int smallExp = 1;
	int smallChange = 0;
	int bigChange = 0;
	int garbage = whitePieces;	

	for( int index = 0; index < 32; index++ ){
		smallMod = pow( 2, smallExp );		
		bigMod = pow( 2, bigExp );
		smallChange = smallMod - 1;
		bigChange = bigMod - 1;

		firstBit = ( garbage % smallMod );
		lastBit = ( garbage % bigMod );
	
		if( lastBit == 1 ){
			if( firstBit == 0 ){
				garbage += smallChange;
				garbage -= bigChange;	
			}
		else{
			if( firstBit == 1 ){
				garbage -= smallChange;
				garbage += bigChange;
			
			}
		}
		smallMod++;
		bigMod--;
	}	
	std::cout << (std::bitset<64>) garbage << std::endl;
*/
}

//Display bitboard in 8x8 configuration
void bbDisp( U64 bb ){
	/* Fills the display Array */

	int displayArray[64];
	U64 garbage;
	garbage = bb;
	int firstBit = 0;	
	
	for( int index = 0; index < 64; index++ ){
		firstBit = (garbage % 2 );
		displayArray[index] = firstBit;
		garbage >>= 1;
	}

	nl(1);
	int count = 0;
	for( int rank = RANK_8; rank >= RANK_1; rank-- ){
		for( int file = FILE_A; file <= FILE_H; file++ )
		{
			count = FR2SQ64( file, rank );
			std::cout << displayArray[count] << " ";	
		}
		nl(1);
	} 
}

/* Search Code (FCD) */

void debugVal(){
	int square;
	std::cout << "Values.\n";
	for( int rank = RANK_8; rank >= RANK_1; rank-- ){
		for( int file = FILE_A; file <= FILE_H; file++){
			square = FR2SQ(file,rank);
			if( getPiece(square) < 10 ) 
				std::cout << " ";
			std::cout << getPiece(square) << " ";
		}
		nl(1);
	}
}

void debugColor(){
	int square;
	std::cout << "Colors.\n";
	for( int rank = RANK_8; rank >= RANK_1; rank-- ){
		for( int file = FILE_A; file <= FILE_H; file++){
			square = FR2SQ(file, rank);
			std::cout << getColor( square ) << " ";
		}
		nl(1);
	}
}

void debugType(){
	int square;
	std::cout << "Types.\n";
	for( int rank = RANK_8; rank >= RANK_1; rank-- ){
		for( int file = FILE_A; file <= FILE_H; file++){
			square = FR2SQ(file,rank);
			std::cout << getType( square ) << " ";
		}
		nl(1);
	}
}

void debugMove(){
	int square;
	std::cout << "Moved.\n";
	for( int rank = RANK_8; rank >= RANK_1; rank-- ){
		for( int file = FILE_A; file <= FILE_H; file++){
			square = FR2SQ(file,rank);
			std::cout << pce[getPiece(square)].moved << " ";
		}
		nl(1);
	}
}

void debugLife(){
	int square;
	std::cout << "Alive.\n";
	for( int rank = RANK_8; rank >= RANK_1; rank-- ){
		for( int file = FILE_A; file <= FILE_H; file++){
			square = FR2SQ(file,rank);
			std::cout << pce[getPiece(square)].life << " ";
		}
		nl(1);
	}
}	

void debugML(){
	//Output Pawn movelist
	int pawn = (board.side == WHITE) ? wPa: bPa;
	for( int i = 0; i < 8; i++ ){
		std::cout << "Pawn " << i + 1 << " movelist is: ";
		for( int j = 0; j < pce[pawn].mL.size(); j++ ){
			std::cout << pce[pawn].mL[j] << " ";
		}
		std::cout << "\n";
		pawn++;
	}
	
	//Output Knight movelist
	int knight = (board.side == WHITE) ? wqN: bqN;
	int change = 5;
	for( int j = 0; j < 2; j++ ){
		std::cout << "Knight Movelist is: ";
		for( int i = 0; i < pce[knight].mL.size(); i++ ){
			std::cout << pce[knight].mL[i] << " ";
		}
		knight +=change;
		std::cout << "\n";
	}

	//Test output of movelists
	int rook = (board.side == WHITE) ? wqR: bqR;
	change = 7;
	for( int i = 0; i < 2; i++){
		std::cout << "The Rooks movelists are: "; 
		for( int j = 0; j < pce[rook].mL.size(); j++ ){
			std::cout << pce[rook].mL[j] << " ";
		}
		std::cout << "\n";
		rook += change;
	}
	nl(1);

	//Test output of movelists
	int king = (board.side == WHITE) ? wK: bK;
	std::cout << "The King movelist are: "; 
	for( int j = 0; j < pce[king].mL.size(); j++ ){
		std::cout << pce[king].mL[j] << " ";
	}
	nl(2);
	
	//Test output of movelists
	int bishop = (board.side == WHITE) ? wqB: bqB;
	change = 3;
	for( int i = 0; i < 2; i++){
		std::cout << "The Bishop movelists are: "; 
		for( int j = 0; j < pce[bishop].mL.size(); j++ ){
			std::cout << pce[bishop].mL[j] << " ";
		}
		std::cout << "\n";
		bishop += change;
	}
	nl(1);

	//Output queen movelist
	int queen = (board.side == WHITE) ? wQ: bQ;
	std::cout << "Queens movelist: ";
	for( int i = 0; i < pce[queen].mL.size(); i++ ){
		std::cout << pce[queen].mL[i] << " ";
	}
	nl(2);


	//Output movelist
	std::cout << "Movelist.\n";
	for( int i = 1; i < board.mL.size() + 1; i++ ){
		std::cout << board.mL[i - 1] << " ";
		if( i % 8 == 0 )
			std::cout << "\n";
	}
	nl(2);

	std::cout << "Undolist.\n";
	for( int i = 1; i < undo.size() + 1; i++){
		std::cout << undo[i - 1].move << " ";
		if( i % 8 == 0 )
			nl(1);
	}
	nl(1);
}

void debugEval(){
	int score = 0;
	int mult;
	mult = (board.side == WHITE) ? 1: -1;
	score = eval() * mult;
	std::cout << "Current Board Evaluation: " << score << "\n";
}
/* debugAll function
 * Used for general debugging 
 * Search Code (FDA)		*/
void debugAll(){
	boardDebug();
	debugVal();
	debugColor();
	debugType();
	debugLife();
	debugMove();
	debugML();
	debugEval();
	bitboardDebug();
	std::cout << "This is ply: " << ply << "\n";
}

