// Board representation

#include "primer.h"
#include "board.h"

void dispMove( int move ){
	int piece = board.sq[move / 100];
	int sq = move % 100;
	char letter = '\0';
	char file = '\0';
	int rank = (sq / 10 - 1);

	//Display piece Letter
	//std::cout << "Move is: " << move << "\n";
	//std::cout << "piece is: " << piece << "\n";
	switch(piece){
		case wqR: 
		case wkR:
		case bqR:
		case bkR: letter = 'R'; break;
		case wqN:
		case wkN:
		case bqN:
		case bkN: letter = 'N'; break;
		case wqB:
		case wkB:
		case bqB:
		case bkB: letter = 'B'; break;
		case wQ:
		case bQ: letter = 'Q'; break;
		case wK:
		case bK: letter = 'K'; break;
		default: letter = 'P';
	}
  
	switch(sq % 10){
		case 1: file = 'a'; break;
		case 2: file = 'b'; break;
		case 3: file = 'c'; break;
		case 4: file = 'd'; break;
		case 5: file = 'e'; break;
		case 6: file = 'f'; break;
		case 7: file = 'g'; break;
		case 8: file = 'h'; break;
	}

	std::cout << letter << file << rank;
}

void dispSq( int sq ){
	char file = '\0';

	switch(sq % 10){
		case 1: file = 'a'; break;
		case 2: file = 'b'; break;
		case 3: file = 'c'; break;
		case 4: file = 'd'; break;
		case 5: file = 'e'; break;
		case 6: file = 'f'; break;
		case 7: file = 'g'; break;
		case 8: file = 'h'; break;
	}

	std::cout << file << (sq / 10) - 1;

}

int getOpp(){
	if( board.side == WHITE )
		return BLACK;
	else
		return WHITE;
}
