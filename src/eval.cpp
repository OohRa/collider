//eval.cpp
#include "eval.h"
#include <primer.h>
#include "board.h"
#include "move.h"
#include "debug.h"
#include "sdl.h"

int evaluate(){

	static int flip[64] = {  56, 57, 58, 59, 60, 61, 62, 63,
				 48, 49, 50, 51, 52, 53, 54, 55,
				 40, 41, 42, 43, 44, 45, 46, 47,
				 32, 33, 34, 35, 36, 37, 38, 39,
				 24, 25, 26, 27, 28, 29, 30, 31,
				 16, 17, 18, 19, 20, 21, 22, 23,
				  8,  9, 10, 11, 12, 13, 14, 15,
				  0,  1,  2,  3,  4,  5,  6,  7 };


	static int pawnTable[64] = {   0,   0,   0,   0,   0,   0,   0,   0,
				      10,  10,  10, -30, -40,  10,  10,  10,
				       5,   0,   5,   0,   0,  -5,  10,  15,
				       0,   0,  10,  25,  30,  10,   5,   0,
				       0,   0,  10,  35,  35,  25,  25,   0,
				      10,  15,  20,  40,  40,  40,  40,   0,
				      80,  80,  80,  80,  80,  80,  80,  80,
				     100, 100, 100, 100, 100, 100, 100, 100 };

	static int knightTable[64] = { -30, -20, -20, -20, -20, -20, -30, -30,
				       -20, -10, -10,  10,  10, -10, -10, -10,
				       -20,   5,  25,   5,   5,  30,  10, -10,
				        10,   5,  10,  15,  20,  20,  20,  10,
				         0,  15,  10,  25,  25,  20,  15,  10,
					 5,  10,  15,  20,  25,  20,  15,  10,
				         0,   5,  20,  10,  10,  25,   5,  25,
			                 0,   0,   0,   0,   0,   0,   0,   0 };

	static int bishopTable[64] = {   0,   0, -20, -10, -10, -20,   0,   0,
				         5,  15,  10,   5,  20,   0,  85,   5,
				       -10,  10,  10,   5,   5,   0,   5, -10,
				        10,  -5,  10,  10,  10,  20,  10,  -5,
				        -5,  20,   5,  15,  15,  10,  30,  10,
				         5,   0,  10,   5,  15,   5,   5,   5,
			               -10,  10,   0,   0,   0,  20,  10,  15,
				         0,   0,   0,   0,   0,   0,   0,   0 };   
			 
	static int rookTable[64] = {    0,   0,   0,  40,  40,   0,   0,   0,
				      -15,   0,   0,   0,   0,   0,   0,   0,
				        0,   0,   0,   0,  10,  15,  10,  10,
				        0,   0,   0,   0,   0,   0,   0,   0,
				        0,   0,   0,   0,   0,   0,   0,   0,
				        0,   0,   0,   0,  10,  15,  10,   5,
				       60,  65,  65,  70,  70,  60,  65,  60,
				        5,  10,  10,  10,  10,  10,  10,  10 };

	static int queenTable[64] = {   0,   0,   5,  20,   0,   0,   0,   0,
					0, -10,  10,  10,   5,   0, -10,   0,
				        0,   0,   0,   5,   0,   5,  10,   5,
					0,   0,   0,   0,   0,   5,   0,   5,
					0,  10,   0,   0,   0,   5,   5,   0,
					0,   0,   0,   0,   0,   0,   0,   0,
				        5,   5,   5,   5,   5,  10,  10,  10,
				       10,  10,  10,  10,  10,  10,  15,  20 };

	static int kingTable1[64] = {  0,  20, -10, -20, -40, -90, 100,  50,
				       0,   0,   0, -30, -80, -20,  10,  15,
				     -20, -30, -40, -50, -50, -40, -30, -20,
				     -50, -50, -50, -50, -50, -50, -50, -50,
				     -50, -50, -50, -50, -50, -50, -50, -50,
			   	     -50, -50, -50, -50, -50, -50, -50, -50,
				     -50, -50, -50, -50, -50, -50, -50, -50,
			  	     -50, -50, -50, -50, -50, -50, -50, -50 }; 
/*
	static int kingTable2[64] = {  -50, -40, -30, -20, -20, 10, -10, -20,
				       -40, -30, -20,   0,  15, 10,   5,   0,
				       -10,   0,   5,  10,  15, 10,   0,   0,
				       -10,   0,   5,  25,  25, 10,   0,   0,
				       -10,   0,   5,  15,  15, 10,   0,   0,
					 0,   0,  10,  10,  10, 10,   0,   0,
				        -5,  -5,   5,   5,   5,  5,   0,   0,
					 0,   0,   0,   0,   0,  0,   0,   0 };
*/
	//Add total material count to score and piece table values
	int score = 0, type, sq;
	int piece = (board.side == WHITE) ? wqR: bqR;
	for( int i = 1; i < 17; i++ ){
		if( pce[piece].life == false ){
			if( piece == wK || piece == bK )
				score -= 999999;
			piece++;
			continue;
		}
		 else{
			score += pce[piece].value;
			sq = indexA.sq[pce[piece].pos];
			type = getType(pce[piece].pos);
			if( ply < 10 && pce[piece].moved > 1 )
				score -= 40;	
			if( board.side == BLACK )
				sq = flip[sq];
			if( type == PAWN ){
				score += pawnTable[sq];
			}
			else if( type == KNIGHT ){
				score += knightTable[sq];
			}
			else if( type == BISHOP ){
				score += bishopTable[sq];
			}
			else if( type == ROOK ){
				score += rookTable[sq];
			}
			else if( type == QUEEN ){
				score += queenTable[sq];
				if( ply < 10 && pce[piece].moved > 1 )
					score -= 100;
			}
			else if( type == KING ) {
				if( pce[piece].pos % 10 == 7 || pce[piece].pos % 10 == 3 )
					score += 50;
				score += kingTable1[sq];
			}
			else{
/*
				std::cout << "What piece is this? " << piece << "\n";
				std::cout << "Type is: " << type << "\n";
				std::cout << "Position is: " << pce[piece].pos << "\n";
				std::cout << "Life is: " << pce[piece].life << "\n";
				//debugAll();
				//SDL_Delay(100000);
*/
			}
		
			
		}
		piece++;
	}
/*
	//Penalize early queen movement
	if( ply < 10 && getType(board.toSq) == QUEEN && getColor(board.toSq) == board.side){
		std::cout << "Moving queen early!\n";
		score -= 200;
	}
*/
/*
	//Penalize moving a piece more than once in the opening
	if( ply < 10 && pce[getPiece(board.toSq)].moved > 1 && getColor(board.toSq) == board.side ){
		//std::cout << "Moving a piece more than once!\n";
		score -= 200;
	}
*/
/* Remove bitboards until implemented in makemove
	//Check for rook open files
	piece = (board.side == WHITE) ? wqR: bqR;
	generateBB();
	U64 bitMask = 0;
	int change = 7;
	for( int i = 0; i < 2; i++ ){
		if( pce[piece].life == false )
			continue;
		sq = indexA.sq[pce[piece].pos];
		bitMask++;
		bitMask <<= sq;
		bitMask = bb.ownPieces ^ bitMask;
		//std::cout << "bitmask is: " << std::bitset<64>(bitMask) << "\n";
		//std::cout << "File bb is: " << std::bitset<64>(bb.file[(pce[piece].pos % 10 - 1)]) << "\n";
		if( (bb.file[(pce[piece].pos % 10 - 1)] & bitMask) == 0 ){
			//std::cout << "Open file!\n";
			score += 200;
		}

		piece += change;			
		bitMask = 0;
	}

*/
	//Check for open ranks (later)
/* Fix this!
	//Check for passed pawns
	piece = (board.side == WHITE) ? wPa: bPa;
	for( int i = 0; i < 8; i++ ){
		if( pce[piece].life == false )
			continue;
		if( pce[piece].pos % 10 == 1 ){
			if( (bb.file[FILE_B] & bb.oppPawn) == 0 ){
				//std::cout << "Passed pawn!\n";
				score += 90;
			}
		}
		else if( pce[piece].pos % 10 == 8 ){
			if( (bb.file[FILE_G] & bb.oppPawn) == 0 ){
				std::cout << "Passed pawn!\n";
				score += 90;
			}
		}
		else{
			if( ((bb.file[pce[piece].pos % 10] & bb.oppPawn) == 0) && ((bb.file[pce[piece].pos % 10 + 2] & bb.oppPawn) == 0) ){
				std::cout << "Passed pawn!\n";
				score += 90; 
			}
		}
		piece++;
	}
*/

/*
	//Add bonus for castling
	if( abs(board.toSq - board.frSq) == 2 && getType(board.toSq) == KING ){
		//std::cout << "Castle Bonus!!!\n";
		score += 500;
	}
*/	
	return score;
}

void generateBB(){
	int piece, square, sq64;
	U64 bitMask = 0;
	bb.ownPieces = 0;
	bb.oppPawn = 0;

	//Fill ownPieces bitboard
	piece = (board.side == WHITE) ? wqR: bqR;
	for(int i = 0; i < 16; i++){
		square = pce[piece].pos;
		sq64 = indexA.sq[square];
		bitMask++;
		bitMask <<= (sq64);
		bb.ownPieces = bb.ownPieces | bitMask;
		bitMask = 0;
		piece++;
	}		
	//std::cout << "Ownpieces bitboard is: " << std::bitset<64>(bb.ownPieces) << "\n";
	
	//Fill opponent pawn bitboard
	piece = (board.side == WHITE) ? bPa: wPa;
	
	for( int i = 0; i < 8; i++ ){
		sq64 = indexA.sq[pce[piece].pos];
		bitMask++;
		bitMask <<= (sq64 - 1);
		bb.oppPawn = bb.oppPawn | bitMask;
		bitMask = 0;
		piece++;
	}
	//std::cout << "Opponent pawn bitboard is: " << std::bitset<64>(bb.oppPawn) << "\n";
}	

int eval(){
	int one = 0, two = 0;
	one = evaluate();
	changeSide();
	two = evaluate();
	changeSide();
	return (one - two);
}
