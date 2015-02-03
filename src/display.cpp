//display.cpp
// Displays the intro and headerscreen

#include <iostream>
#include "primer.h"
#include "display.h"

void displayHeader(){
	int count = 0;
	for( count = 0; count < 1000; count++){
		nl(1);
		stars(60);
	}
}

void displayBoard(boardStruct &board){
	int rank, file, square120, piece;
	std::string showPiece;

	nl(1);
	stars(60);
	nl(1);
	stars(60);
	nl(1);
	stars(60);
	nl(2);

	//Display board as symbols
	spaces(15);
	printf("Board\n\n");		
	spaces(15);
	for( rank = RANK_8; rank >= RANK_1; rank--){
		for( file = FILE_A; file <= FILE_H; file++){
			square120 = FR2SQ(file,rank);
			piece = board.sq120[square120];
			switch ( piece ){
				case  0: showPiece = "*"; break;
				case  1:
				case  8: showPiece = "R"; break;
				case  2: 
				case  7: showPiece = "N"; break;
				case  3:
				case  6: showPiece = "B"; break;
				case  4: showPiece = "Q"; break;
				case  5: showPiece = "K"; break;
				case  9:
				case 10:
				case 11:
				case 12:
				case 13:
				case 14:
				case 15:
				case 16: showPiece = "P"; break;
				case 17:
				case 24: showPiece = "r"; break;
				case 18:
				case 23: showPiece = "n"; break;
				case 19:
				case 22: showPiece = "b"; break;
				case 20: showPiece = "q"; break;
				case 21: showPiece = "k"; break;
				case 25:
				case 26:
				case 27:
				case 28:
				case 29:
				case 30:
				case 31:
				case 32: showPiece = "p"; break;
				default: printf(" ERROR ");
			}
			
			spaces(1);	
			std::cout << showPiece;
		}
		nl(1);
		spaces(15);
	}
	nl(1);
	stars(60);
	nl(1);
	stars(60);
	nl(1);
	stars(60);
	nl(30);	

}

void displayBitboard( U64 bbDisplay ){
	/* Fills the display Array */
	int displayArray[64];
	int firstBit, count;
	U64 garbage;
	garbage = bbDisplay;
	
	for( int index = 0; index < 64; index++ ){
		firstBit = (garbage % 2 );
		displayArray[index] = firstBit;
		garbage >>= 1;
	}

	for( int rank = RANK_8; rank >= RANK_1; rank-- ){
		for( int file = FILE_A; file <= FILE_H; file++ ){
			count = FR2SQ64( file, rank );
			std::cout << displayArray[count] << " ";	
		}
		nl(1);
	} 

}

int displayGraphics(){
return 0;
}

void displayAll(boardStruct &board){
//	displayHeader();
	displayBoard(board);
}

void nl(int lines){
	for(int lineCount = 0; lineCount < lines; lineCount++){
		printf("\n");
	}
}

void stars(int stars){
	for( int starCount = 0; starCount < stars; starCount++){
		printf("*");
	}
}

void spaces(int spaces){
	for( int spaceCount = 0; spaceCount < spaces; spaceCount++){
		printf(" ");
	}
}
