//debug.cpp
// Use for writing functions to test 

#include <iostream>
#include "primer.h"
#include "debug.h"
#include "display.h"

void boardDebug( boardStruct &board, pieceStruct pieces[] ){

	int rank, file, square64, square120;

	//Printing both boards for debugging
	
	printf("Board64 by file and rank.\n\n");
	for( rank = RANK_8; rank >= RANK_1; rank--)
	{
		for( file = FILE_A; file <= FILE_H; file++)
		{
			square64 = FR2SQ64(file, rank);
			if( board.sq64[square64] < 10 )
			{
				spaces(1);
			}	
			printf("%d ", board.sq64[square64]);
		}
		nl(1);
	}
	nl(1);
	stars(30);
	nl(1);

		//Change board.sq120 to output all squares in right order	
	printf("Board120 by file and rank.\n\n");
	for( rank = RANK_8; rank >= RANK_1; rank--)
	{
		for( file = FILE_A; file <= FILE_H; file++)
		{
			square120 = FR2SQ( file , rank);
			if( board.sq120[square120] < 10 )
			{
				spaces(1);
			}
			printf("%d ", board.sq120[square120]);
		}
		nl(1);
	}
	nl(1);	
	stars(60);
	nl(1);

	
	for( int index = 1; index <= 32; index++)
	{
		printf("%d ", pieces[index].position);
		nl(1);
	}		
	
}



void bitboardDebug()
{
	/* Displays bitboards for debugging */
/*
	cout << "\"White Rooks\"" << endl;
	cout << (bitset<64>) whiteRooks << endl;
	cout << "\"White Knights\"" << endl;
	cout << (bitset<64>) whiteKnights << endl;
	cout << "\"White Bishops\"" << endl;
	cout << (bitset<64>) whiteBishops << endl;
	cout << "\"White Queen\"" << endl;
	cout << (bitset<64>) whiteQueen << endl;
	cout << "\"White King\"" << endl;
	cout << (bitset<64>) whiteKing << endl;
	cout << "\"White Pawns\"" << endl;
	cout << (bitset<64>) whitePawns << endl;
	cout << "\"White Pieces\"" << endl;
	cout << (bitset<64>) whitePieces << endl;
	nl(1);
	
	cout << "\"Black Rooks\"" << endl;
	cout << (bitset<64>) blackRooks << endl;
	cout << "\"Black Knights\"" << endl;
	cout << (bitset<64>) blackKnights << endl;
	cout << "\"Black Bishops\"" << endl;
	cout << (bitset<64>) blackBishops << endl;
	cout << "\"Black Queen\"" << endl;
	cout << (bitset<64>) blackQueen << endl;
	cout << "\"Black King\"" << endl;
	cout << (bitset<64>) blackKing << endl;
	cout << "\"Black Pawns\"" << endl;
	cout << (bitset<64>) blackPawns << endl;
	cout << "\"Black Pieces\"" << endl;
	cout << (bitset<64>) blackPieces << endl;
	nl(1);

	cout << "\"Occupied Squares\"" << endl;
	cout << (bitset<64>) occupiedSquares << endl;

	cout << "\"Empty Squares\"" << endl;
	cout << (bitset<64>) emptySquares << endl;
*/	
	/* Reverses bitboard and displays */
/*     Reverse by 64 steps 	
	U64 bbReverse = 0;
	U64 garbage;
	U64 firstBit;
	
	garbage = whiteRooks;
	
	for( int index = 0; index < 63; index++ )	
	{
		firstBit = ( garbage % 2 );
		if( firstBit == 1 )	
			bbReverse++;

		bbReverse <<= 1;
		garbage >>= 1;
	}

	nl(10);	
	cout << (bitset<64>) bbReverse << endl;
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

	for( int index = 0; index < 32; index++ )
	{
		smallMod = pow( 2, smallExp );		
		bigMod = pow( 2, bigExp );
		smallChange = smallMod - 1;
		bigChange = bigMod - 1;

		firstBit = ( garbage % smallMod );
		lastBit = ( garbage % bigMod );
	
		if( lastBit == 1 )
		{
			if( firstBit == 0 )
			{	garbage += smallChange;
				garbage -= bigChange;	
			}
		else
		{
			if( firstBit == 1 )
				garbage -= smallChange;
				garbage += bigChange;
			
		}
		}
		smallMod++;
		bigMod--;
	}	
	cout << (bitset<64>) garbage << endl;
*/
	/* Fills the display Array */
/*
	int displayArray[64];
	U64 garbage;
	garbage = whiteRooks;
	int firstBit = 0;	
	
	for( int index = 0; index < 63; index++ )
	{
		firstBit = (garbage % 2 );
		displayArray[index] = firstBit;
		garbage >>= 1;
	}

	int count = 0;
	for( int rank = RANK_8; rank >= RANK_1; rank-- )
	{
		for( int file = FILE_A; file <= FILE_H; file++ )
		{
			count = FR2SQ64( file, rank );
			cout << displayArray[count] << " ";	
		}
		nl(1);
	} 
*/	
}

