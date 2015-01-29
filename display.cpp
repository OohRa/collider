// Displays the intro and headerscreen

#include "primer.h"
#include "stdio.h"
#include "stdlib.h"

void displayHeader()
{
	int count = 0;
	for( count = 0; count < 1000; count++)
	{
		nl(1);
		stars(60);
	}
}

void displayBoard()
{
	int rank = RANK_8;
	int file = FILE_A;
//	int square64 = 0;
	int square120 = 0;
//	int index = 0;
//	int count = 0;

	nl(1);
	stars(60);
	nl(1);
	stars(60);
	nl(1);
	stars(60);
	nl(2);

	//Printing both boards for debugging
	/*
	printf("Board64 by file and rank.\n\n");
	for( rank = RANK_8; rank >= RANK_1; rank--)
	{
		for( file = FILE_A; file <= FILE_H; file++)
		{
			square64 = FR2SQ64(file, rank);
			if( board64[square64] < 10 )
			{
				spaces(1);
			}	
			printf("%d ", board64[square64]);
		}
		nl(1);
	}
	nl(1);
	stars(30);
	nl(1);
*/
/*		Change board120 to output all squares in right order	
	printf("Board120 by file and rank.\n\n");
	for( rank = RANK_8; rank >= RANK_1; rank--)
	{
		for( file = FILE_A; file <= FILE_H; file++)
		{
			square120 = FR2SQ( file , rank);
			if( board120[square120] < 10 )
			{
				spaces(1);
			}
			printf("%d ", board120[square120]);
		}
		nl(1);
	}
	nl(1);	
	stars(60);
	nl(1);
*/
	//Display board as symbols
/*	printf("Board with piece symbols\n\n");		*/
	spaces(15);
	for( rank = RANK_8; rank >= RANK_1; rank--)
	{
		for( file = FILE_A; file <= FILE_H; file++)
		{
			square120 = FR2SQ(file,rank);
			int piece = 0;
			piece = board120[square120];
			std::string showPiece = "0";
			switch ( piece )
			{
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
			cout << showPiece;
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
	nl(1);
	
	/*
	for( index = 1; index <= 32; index++)
	{
		printf("%d ", pieceList[index].position);
		nl(1);
	}		
	*/
}

void displayBitboard( U64 bbDisplay )
{
	/* Fills the display Array */

	int displayArray[64];
	U64 garbage;
	garbage = bbDisplay;
	int firstBit = 0;	
	
	for( int index = 0; index < 64; index++ )
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

}

int displayGraphics(){


return 0;

}

void displayAll()
{

//	displayHeader();
	displayBoard();

}
