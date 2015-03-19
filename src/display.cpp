//display.cpp
// Displays the intro and headerscreen

#include <iostream>
#include "primer.h"
#include "display.h"
#include "board.h"
#include "sdl.h"
#include "debug.h"

void nl(int lines){
	for(int lineCount = 0; lineCount < lines; lineCount++){
		printf("\n");
	}
}

void fill(int num, char fill){
	for( int fillCount = 0; fillCount < num; fillCount++){
		std::cout << fill;
	}
}

void displayHeader(){
	int count = 0;
	for( count = 0; count < 1000; count++){
		nl(1);
		fill(60, '*');
	}
}
//FDB
void displayBoard(){
	int rank, file, square120, piece, color;
	std::string showPiece;
	color = 0;
	//Display board as symbols
	printf("Board\n\n");		
	fill( 15, ' ' );
	fill( 44, '$' );
	nl(1);
	fill( 15, ' ' );
	std::cout << "$|";
	for( rank = RANK_8; rank >= RANK_1; rank--){
		for( file = FILE_A; file <= FILE_H; file++){
			square120 = FR2SQ(file,rank);
			piece = board.sq[square120];
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
				default: printf("?");
			}
			color++;
			//Only Use parentheses if square has a piece on it
			if( showPiece != "*" ){
				if( getColor(square120) == WHITE ){
				 std::cout << "|(" << showPiece << ")|";
				}
				else std::cout << "|[" << showPiece << "]|";
			}
			else{	
			std::cout << "| ";
			std::cout << showPiece;
			std::cout << " |";
			}
			
		}
		std::cout << "|$\n";
		fill(15, ' ');
		if( rank != RANK_1 ){
			std::cout << "$||";
			fill(38, ' ');
			std::cout << "||$";
			nl(1);
			fill( 15, ' ' );
			std::cout << "$|";
		}
		color--;
	}
	fill(44, '$');
	nl(1);
}

//FDBB
void displayBitboard(){
	/* Fills the display Array */
	int displayArray[64];
	int firstBit, count;
	U64 garbage;
	U64 bbDisplay = 0;
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

//FDG
int displayGraphics(){
	int piece, square, colorSq, colorCount;
	SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );
	SDL_RenderClear(gRenderer);
	SDL_Rect rSquare;
	int showPiece;
	colorCount = 1;
	for( int rank = RANK_8; rank >= RANK_1; rank-- ){
		for( int file = FILE_A; file <= FILE_H; file++ ){
		square = FR2SQ(file,rank);
		piece = board.sq[square];
		if( colorCount % 2 == 0 ) colorSq = BLACK;
		else colorSq = WHITE;

		switch ( piece ){
			case  0: showPiece = EMPTY; break;
			case  1:
			case  8: showPiece = gWR; break;
			case  2: 
			case  7: showPiece = gWN; break;
			case  3:
			case  6: showPiece = gWB; break;
			case  4: showPiece = gWQ; break;
			case  5: showPiece = gWK; break;
			case  9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16: showPiece = gWP; break;
			case 17:
			case 24: showPiece = gBR; break;
			case 18:
			case 23: showPiece = gBN; break;
			case 19:
			case 22: showPiece = gBB; break;
			case 20: showPiece = gBQ; break;
			case 21: showPiece = gBK; break;
			case 25:
			case 26:
			case 27:
			case 28:
			case 29:
			case 30:
			case 31:
			case 32: showPiece = gBP; break;
			default: printf("?");
		}
		
		//For promoted pawns
		if((( showPiece >= wPa && showPiece <= wPh ) || ( showPiece >= bPa && showPiece <= bPh )) && pce[showPiece].type == QUEEN ){
			if( pce[showPiece].color == WHITE )
				showPiece = wQ;
			else if( pce[showPiece].color == BLACK )	
				showPiece = bQ;
			else 
				std::cout << "AGH HELP!";
		}

		 if( !flipFlag ){
			rSquare = { (file * 75), ((7-rank) * 75), 75, 75 };
		}
		else
			rSquare = { ((7 - file) * 75), ((rank) * 75), 75, 75 };
		SDL_RenderCopy( gRenderer, squareTextures[colorSq], NULL, &rSquare );
		if( showPiece != EMPTY )
		SDL_RenderCopy( gRenderer, pieceTextures[showPiece], NULL, &rSquare );	
		colorCount++;
		}
		colorCount++;
	}
	SDL_RenderPresent(gRenderer);
	return 0;
}

//FDA
void displayAll(){
//	displayHeader();
//	displayBoard();
	displayGraphics();
}

