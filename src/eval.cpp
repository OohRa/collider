
#include "eval.h"
#include <primer.h>
#include "board.h"
#include "move.h"
#include "debug.h"
#include "sdl.h"

	int flip[64] = {         56, 57, 58, 59, 60, 61, 62, 63,
				 48, 49, 50, 51, 52, 53, 54, 55,
				 40, 41, 42, 43, 44, 45, 46, 47,
				 32, 33, 34, 35, 36, 37, 38, 39,
				 24, 25, 26, 27, 28, 29, 30, 31,
				 16, 17, 18, 19, 20, 21, 22, 23,
				  8,  9, 10, 11, 12, 13, 14, 15,
				  0,  1,  2,  3,  4,  5,  6,  7 };


	int pawnTable[64] = {          0,   0,   0,   0,   0,   0,   0,   0,
				       0,   0, -15, -20, -20, -10,   0,   0,
				       5,   5,   5,   5,   5,   5,  10,  15,
				       5,   5,  20,  30,  35,  10,   5,   5,
				      17,  17,  10,  35,  35,  25,  25,  10,
				      15,  35,  40,  40,  40,  40,  30,  15,
				      80,  80,  80,  80,  80,  80,  80,  80,
				       0,   0,   0,   0,   0,   0,   0,   0 };

	int pawnTable2[64] = {          0,   0,   0,   0,   0,   0,   0,   0,
				      -20, -20, -20, -20, -20, -20, -20, -20,
				       5,   5,   5,   5,   5,   5,  10,  15,
				      15,  15,  10,  25,  30,  10,  15,  25,
				      17,  17,  50,  35,  35,  25,  55,  10,
				      45,  60,  60,  60,  60,  60,  60,  45,
				      60,  80,  80,  80,  80,  80,  80,  60,
				       0,   0,   0,   0,   0,   0,   0,   0 };
	
	int knightTable[64] = {        -30, -20,   0,   0,   0, -10, -30, -30,
				         0,   0,   0,  10,  10,   0,   0,   0,
				         0,   5,  15,   5,   5,  15,  10,   0,
				         0,   5,  10,  15,  20,  20,  20,   0,
				         0,  15,  10,  25,  25,  20,  15,   0,
					 0,  10,  15,  20,  25,  20,  15,   0,
				         0,   5,  20,  10,  10,  25,   5,   5,
			               -30,   0,   0,   0,   0,   0,   0, -30 };

	int bishopTable[64] = {          0,   0, -20,   0,   0, -20,   0,   0,
				         5,  10,   0,   5,  10,   0,  15,   5,
				         0,   0,   5,  15,  10,   0,   0,   0,
				         0,   5,  20,   5,   5,  15,   5,   0,
				         5,  20,   5,  15,  15,  10,  20,   0,
				         5,   0,  10,   5,  15,   5,   5,   0,
			                 0,   0,   0,   0,   0,   0,   0,   0,
				         0,   0,   0,   0,   0,   0,   0,   0 };   
			 
	int rookTable[64] = {           0,  10,  20,  40,  40,  20,  10,   0,
				        0,   0,   0,   0,   0,   0,   0,   0,
				        0,   0,   0,   0,  10,  15,  10,  10,
				        0,   0,   0,   0,   0,   0,   0,   0,
				        0,   0,   0,   0,   0,   0,   0,   0,
				        0,   0,   0,   0,   0,   5,   0,   5,
				       50,  50,  50,  50,  50,  50,  50,  50,
				       20,  20,  20,  20,  20,  20,  20,  20 };

	int queenTable[64] = {          0,   0,   5, -10,   0,   0,   0,   0,
					0,   0,  10,  10,  10,   0,   0,   0,
				        0,   0,   0,   5,   0,   0,   0,   0,
					0,   0,   0,   0,   0,   5,   0,   5,
					0,  10,   0,   0,   0,   5,   5,   0,
					0,   0,   0,   0,   0,   0,   0,   0,
				        5,   5,   5,   5,   5,  10,  10,  10,
				       10,  10,  10,  10,  10,  10,  15,  20 };

	int kingTable1[64] = {        20,  40,  20, -20, -40, -50,  50,  40,
				       0,   0,   0, -30, -80, -20,  10,  15,
				     -20, -30, -40, -50, -50, -40, -30, -20,
				     -50, -50, -50, -50, -50, -50, -50, -50,
				     -50, -50, -50, -50, -50, -50, -50, -50,
			   	     -50, -50, -50, -50, -50, -50, -50, -50,
				     -50, -50, -50, -50, -50, -50, -50, -50,
			  	     -50, -50, -50, -50, -50, -50, -50, -50 }; 

	int kingTable2[64] = {         -50, -40, -10,   0,   0,  5, -40, -20,
				        10,  10,  15,  20,  15, 15,  10,   5,
				        15,  15,  15,  20,  25, 10,  15,  10,
				        10,  10,  15,  25,  25, 15,  10,  10,
				        10,  10,  15,  25,  25, 15,  30,  10,
					10,  10,  10,  25,  20, 15,  30,  10,
				        15,  15,  35,  35,  35, 35,  30,  10,
					 0,   0,   0,   0,   0,  0,   0,   0 };
int evaluate(){

	
	//Add total material count to score and piece table values
	int score = 0, type = 0, sq = 0;
	int piece = (board.side == WHITE) ? wqR: bqR;
	int bPair = 0;
	bool endgame = false;
	int king = (board.side == WHITE) ? wK: bK;
	int mod = (board.side == WHITE) ? 1: -1;
	int opp = getOpp();

	//Material Count
	score += board.material[board.side];

	//Determine endgame
	if( score < 102000 ){
		endgame = true;
		std::cout << "Endgame!\n";
	}

	piece = (board.side == WHITE) ? wqR: bqR;
	//Extra Count
	for( int i = 1; i < 17; ++i ){
		if( pce[piece].life == false ){
			piece++;
			continue;
		}
		sq = indexA.sq[pce[piece].pos];
		type = getType(pce[piece].pos);
		if( board.side == BLACK )
			sq = flip[sq];
		if( type == PAWN ){
			if( endgame )
				score += pawnTable2[sq];
			else
				score += pawnTable[sq];
		}
		else if( type == KNIGHT ){
			score += knightTable[sq];
		}
		else if( type == BISHOP ){
			score += bishopTable[sq];
			bPair++;
			if( bPair == 2 )
				score += 50;
		}
		else if( type == ROOK ){
			score += rookTable[sq];
		}
		else if( type == QUEEN ){
			score += queenTable[sq];
			if( ply < 10 && pce[piece].moved > 1 ){
				score -= 50;
			}
		}
		else if( type == KING ) {
			if(board.castled[board.side]){
				std::cout << "Castled\n";
				score += 50;
			}
			if( endgame )
				score += kingTable2[sq];
			else 
				score += kingTable1[sq];
		}
		else{
			std::cout << "What\n";
		}
		
		piece++;	
		}

	//King Safety
	if(board.castled[board.side]){
		int test = 0;
		sq = pce[king].pos + mod * 9; 
		for( int i = 0; i < 3; ++i ){
			if( getType(sq) == PAWN && getColor(sq) == board.side ){
				score += 10;
				test += 10;
			}
			sq += mod;
		}
		std::cout << "King Safety score = " << test << "\n";
	
	}
	
	//Passed pawns with advanced bitboards
	piece = (board.side == WHITE) ? wPa: bPa;	
	for( int i = piece; i < piece + 7; ++i ){
		if( pce[i].life == true ){
			if( (bb.passPwn[board.side][pce[i].pos-31] & bb.pawns[opp]) == 0 ){
				bbDisp( bb.passPwn[board.side][pce[i].pos - 31] );
				bbDisp( bb.pawns[opp] );
				bbDisp( pce[i].bitboard );
				std::cout << "Side is " << board.side << "\n";
				std::cout << "Piece is: " << i << "\n";
				std::cout << "Passed pawn!\n";
				score += 50;
			}
		}
	}

	//Doubled pawns check
	int dblPawns[8] = {0,0,0,0,0,0,0,0};
	int testSq = 0;

	piece = (board.side == WHITE) ? wPa: bPa;	
/*
	//Check pawns on files	
	for( int i = piece; i < piece + 7; ++i ){
		testSq = pce[i].pos % 10;
		if( pce[i].life == true )
			dblPawns[testSq - 1] += 1;

		//Passed and isolated pawns
		if( pce[i].pos % 10 == 1 ){
			//Passed
			//if( bb.pawns[getOpp()
			if(( bb.pawns[getOpp()] & bb.file[1]) == 0 ){
				std::cout << "Passed a-file pawn.\n";
				score += 40;
			}
			//Isolated
			if(( bb.pawns[board.side] & bb.file[1]) == 0 ){
				std::cout << "Isolated a-file pawn.\n";
				score -= 20;
			}
			
		}
		else if( pce[i].pos % 10 == 8 ){
			//Passed
			if(( bb.pawns[getOpp()] & bb.file[7]) == 0 ){
				std::cout << "Passed g-file pawn.\n";
				score += 40;
			}
			//Isolated
			if(( bb.pawns[board.side] & bb.file[7]) == 0 ){
				std::cout << "Isolated h-file pawn.\n";
				score -= 20;
			}
		}
		else{
			//Passed
			if( (bb.pawns[getOpp()] & bb.file[pce[i].pos % 10 - 1]) == 0){
				if( (bb.pawns[getOpp()] & bb.file[pce[i].pos % 10 + 1]) == 0){
					std::cout << "Passed pawn.\n";
					score += 50;
				}
			}
			//Isolated
			if(( bb.pawns[board.side] & bb.file[pce[i].pos % 10 - 1]) == 0){
				if( (bb.pawns[board.side] & bb.file[pce[i].pos % 10 + 1]) == 0){
					std::cout << "Isolated pawn.\n";
					score -= 20;
				}
			}
		}
	}
*/
	//Subtract points for doubled pawns
	for( int i = 0; i < 8; ++i ){
		if( dblPawns[i] > 1 ){
			//std::cout << "Double pawns " << dblPawns[i] << "\n";
			//std::cout << "Score is " << score;
			score -= (dblPawns[i] - 1) * 20;
			//std::cout << "Score is " << score;
			dblPawns[i] = 0;
			//std::cout << "Side is " << board.side << "\n";
			std::cout << "Double pawns subtraction\n";
		}
	}
 
	//Open files check
	piece = (board.side == WHITE) ? wqR: bqR;
	for( int i = piece; i <= piece + 7; i += 7 ){
		if( pce[i].life == false ){
			++i;
			continue;
		}
		else{
			testSq = (pce[i].pos % 10) - 1;
			//std::cout << "Testsq is " << testSq << "\nPiece is " << i << "\n";
			//std::cout << "Side is " << board.side << "\n";
			if( (bb.file[testSq] & bb.pawns[board.side]) == 0 ){
				score += 20;
				std::cout << "Rook on open file yes.\n";
			}
		}
	}

	//Battery check
	piece = (board.side == WHITE) ? wqR: bqR;
	if( pce[piece].pos % 10 == pce[piece + 7].pos % 10 ){
		score += 20;
		std::cout << "Rook battery\n";
	}

	//

	return score;
}

/*
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
*/
int eval(){
	int one = 0, two = 0;
	one = evaluate();
	//one -= 25;
	changeSide();
	two = evaluate();
	changeSide();
	return (one - two);
}

