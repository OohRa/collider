// Board representation

#include "primer.h"
#include "stdio.h"


void makeMove()
{

	if( stop )
		return;	

	/* Makes the users move */
	int piece;
	piece = board120[fromSquare];
	board120[fromSquare] = EMPTY;
	board120[toSquare] = piece;
	//Switches sides
	if( side == WHITE )
		side = BLACK;
	else side = WHITE;	

}
	
