//legal.cpp

//Holds all functions involved in checking legality of moves.

#include <iostream>
#include "primer.h"
#include "stdio.h"
#include "stdlib.h"

/* Check if the user or cpu move is legal */
bool checkLegal()
{
	int piece = 0;
	int pieceType = 0;
	int pieceColor;
	int toColor;
	int toValue;
	piece = board120[fromSquare];
	toValue = board120[toSquare];
	bool check = false;
	
	//Exits out of the game loop.
	if( stop )
		return false;


	//Checks which color the piece is and defines it.
	if( piece >= wqR && piece <= wPh )
		pieceColor = WHITE;

	if( piece >= bqR && piece <= bPh )
		pieceColor = BLACK; 
	if( piece == EMPTY )
		pieceColor = NONE;
	//Checks what color, if any, the to square is.
	if( toValue >= wqR && toValue <= wPh )
		toColor = WHITE;

	if( toValue >= bqR && toValue <= bPh )
		toColor = BLACK;

	if( toValue == EMPTY )
		 toColor = NONE;	
	// Error check for invalid moves
	if(( side == WHITE) && (pieceColor == BLACK) )
	{
		cout << "Invalid move. White to move. " << endl;
		return false;
	}
	
	else if(( side == BLACK) && (pieceColor == WHITE))
	{
		cout << "Invalid move. Black to move." << endl;
		return false;
	}
	
	if( piece == NONE )
	{
		cout << "Invalid move. Empty square." << endl;
		return false;
	}
	
	if( toColor == side ) 
	{
		cout << "Invalid move. Don't take your own piece." << endl;
		return false;
	}
	
	//Check what type the piece is.
	switch ( piece )
	{
		case wqR:
		case wkR:
		case bqR:
		case bkR: pieceType = ROOK; break;
		case wqN:
		case wkN:
		case bqN:
		case bkN: pieceType = KNIGHT; break;
		case wqB:
		case wkB:
		case bqB:
		case bkB: pieceType = BISHOP; break;
		case  wQ: 
		case  bQ: pieceType = QUEEN; break;
		case  wK:
		case  bK: pieceType = KING; break;
		default: pieceType = PAWN; break;
	}	
	/* Bunch of if statements to check for each piece if the move is legal. */

	// Check for valid knight moves
	if( pieceType == KNIGHT )
	{
		int index = 0;
		int knightLegal[8];

		knightLegal[0] = (fromSquare - 21);
		knightLegal[1] = (fromSquare - 19);
		knightLegal[2] = (fromSquare - 12);
		knightLegal[3] = (fromSquare -  8);
		knightLegal[4] = (fromSquare +  8);
		knightLegal[5] = (fromSquare + 12);
		knightLegal[6] = (fromSquare + 19);
		knightLegal[7] = (fromSquare + 21);

		for( index = 0; index < 8; index++ )
		{
			if( knightLegal[index] == toSquare )
				return true;
		}
		
		cout << "Invalid move. Knights don't move like that." << endl;
		return false;
		
	}
	// Check if rook move is legal.
	if( pieceType == ROOK )
	{
		int rookLegal[14];
		int valid;
		int countSq;
		int index;
		int checkSq;
		int count;
		int difference;
		int checkDifference;
		int opposite = !side;	
	
		//If rook movement is vertical.
		difference = ((toSquare - fromSquare) % 10 );
		checkDifference = abs(toSquare - fromSquare);
	
		if( difference != 0 && (checkDifference > 7) )
		{
			cout << "Invalid move. Rooks don't move like that." << endl;
			return false;
		}
		if( difference == 0 )	
		{
			if( toSquare > fromSquare )
			{
				for( countSq = (fromSquare + 10); countSq < toSquare; countSq += 10 )
				{
					checkSq = board120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == toSquare )
					{
						return true;
						break;
					}
			
					if( toColor == side )
					{	
						cout << "Invalid move. Rook can't move through it's own piece." << endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						cout << "Invalid move. Offboard square." << endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						cout << "Invalid move. Rook can't move through pieces." << endl;
						return false;
					}	
				}
		}	
				if( toSquare < fromSquare )
				{	
					for( countSq = (fromSquare - 10); countSq > toSquare; countSq -= 10 )
					{
						checkSq = board120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == toSquare )
						{
							return true;
						}
				
						if( toColor == side )
						{
							cout << "Invalid move. Rook can't move through it's own piece." << endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							cout << "Invalid move. Offboard square." << endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							cout << "Invalid move. Rook can't move through pieces." << endl;
							return false;
						}
					}
				}
		}
		else if( difference != 0 )
		{
			if( toSquare > fromSquare )
			{
				for( countSq = (fromSquare + 1); countSq < toSquare; countSq += 1 )
				{
					checkSq = board120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == toSquare )
					{
						return true;
						break;
					}
			
					if( toColor == side )
					{	
						cout << "Invalid move. Rook can't move through it's own piece." << endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						cout << "Invalid move. Offboard square." << endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						cout << "Invalid move. Rook can't move through pieces." << endl;
						return false;
					}	
				}
		}	
				if( toSquare < fromSquare )
				{	
					for( countSq = (fromSquare - 1); countSq > toSquare; countSq -= 1 )
					{
						checkSq = board120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == toSquare )
						{
							return true;
						}
				
						if( toColor == side )
						{
							cout << "Invalid move. Rook can't move through it's own piece." << endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							cout << "Invalid move. Offboard square." << endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							cout << "Invalid move. Rook can't move through pieces." << endl;
							return false;
						}
					}
				}
		}
	}
				
	if( pieceType == BISHOP )
	{
		int valid;
		int countSq;
		int index;
		int checkSq;
		int count = 0;
		int difference = 0;
		int checkDifference;
		int opposite = !side;	


		checkDifference = ((toSquare - fromSquare) % 9 );
		difference = ((toSquare - fromSquare) % 11 );
	
		/* Negate any move that isn't a diagonal */
		if( difference != 0 && checkDifference != 0 )
		{
			cout << "Invalid move. Bishop can't move like that." << endl;
			return false;
		}
		
		/* If movement is on the right diagonal then check path */
		if( difference == 0 )	
		{
			if( toSquare > fromSquare )
			{
				for( countSq = (fromSquare + 11); countSq < toSquare; countSq += 11 )
				{
					checkSq = board120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == toSquare )
					{
						return true;
						break;
					}
			
					if( toColor == side )
					{	
						cout << "Invalid move. Bishop can't move through it's own piece." << endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						cout << "Invalid move. Offboard square." << endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						cout << "Invalid move. Bishop can't move through pieces." << endl;
						return false;
					}	
				}
			}	
				if( toSquare < fromSquare )
				{	
					for( countSq = (fromSquare - 11); countSq > toSquare; countSq -= 11 )
					{
						checkSq = board120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == toSquare )
						{
							return true;
						}
				
						if( toColor == side )
						{
							cout << "Invalid move. Bishop can't move through it's own piece." << endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							cout << "Invalid move. Offboard square." << endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							cout << "Invalid move. Bishop can't move through pieces." << endl;
							return false;
						}
					}
				}
		}
	
		/* If movement is on left diagonal then check path */
		if( checkDifference == 0 )
		{
			if( toSquare > fromSquare )
			{
				for( countSq = (fromSquare + 9); countSq < toSquare; countSq += 9 )
				{
					checkSq = board120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == toSquare )
					{
						return true;
						break;
					}
			
					if( toColor == side )
					{	
						cout << "Invalid move. Bishop can't move through it's own piece." << endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						cout << "Invalid move. Offboard square." << endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						cout << "Invalid move. Bishop can't move through pieces." << endl;
						return false;
					}	
				}
			}	
				if( toSquare < fromSquare )
				{	
					for( countSq = (fromSquare - 9); countSq > toSquare; countSq -= 9 )
					{
						checkSq = board120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == toSquare )
						{
							return true;
						}
				
						if( toColor == side )
						{
							cout << "Invalid move. Bishop can't move through it's own piece." << endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							cout << "Invalid move. Offboard square." << endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							cout << "Invalid move. Bishop can't move through pieces." << endl;
							return false;
						}
					}
				}
			}
				
		}
	
	
	if( pieceType == QUEEN )
	{
		int valid;
		int countSq;
		int index;
		int checkSq;
		int count = 0;
		int difference = 0;
		int opposite = !side;	
	
		//If queen movement is vertical.
		difference = ((toSquare - fromSquare) % 10 );
		if( difference == 0 )	
		{
			if( toSquare > fromSquare )
			{
				for( countSq = (fromSquare + 10); countSq < toSquare; countSq += 10 )
				{
					checkSq = board120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == toSquare )
					{
						return true;
						break;
					}
			
					if( toColor == side )
					{	
						cout << "Invalid move. Queen can't move through it's own piece." << endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						cout << "Invalid move." << endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						cout << "Invalid move. Queen can't move through pieces." << endl;
						return false;
					}	
				}
		}	
				if( toSquare < fromSquare )
				{	
					for( countSq = (fromSquare - 10); countSq > toSquare; countSq -= 10 )
					{
						checkSq = board120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == toSquare )
						{
							return true;
						}
				
						if( toColor == side )
						{
							cout << "Invalid move. Queen can't move through it's own piece." << endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							cout << "Invalid move." << endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							cout << "Invalid move. Queen can't move through pieces." << endl;
							return false;
						}
					}
				}
		}
		else if( difference != 0 )
		{
			difference = (toSquare - fromSquare) % 11;
			if( difference == 0 )
			{
			if( toSquare > fromSquare )
			{
				for( countSq = (fromSquare + 11); countSq < toSquare; countSq += 11 )
				{
					checkSq = board120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == toSquare )
					{
						return true;
						break;
					}
			
					if( toColor == side )
					{	
						cout << "Invalid move. Queen can't move through it's own piece." << endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						cout << "Invalid move." << endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						cout << "Invalid move. Queen can't move through pieces." << endl;
						return false;
					}	
				}
			}	
				if( toSquare < fromSquare )
				{	
					for( countSq = (fromSquare - 11); countSq > toSquare; countSq -= 11 )
					{
						checkSq = board120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == toSquare )
						{
							return true;
						}
				
						if( toColor == side )
						{
							cout << "Invalid move. Queen can't move through it's own piece." << endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							cout << "Invalid move." << endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							cout << "Invalid move. Queen can't move through pieces." << endl;
							return false;
						}
					}
				}
				}
				else if( difference != 0 )
				{
					int checkDifference;
					difference = (toSquare - fromSquare) % 9;
					checkDifference = difference;
					if( difference == 0 )
					{
						if( checkDifference == 0 )
						{
						if( toSquare > fromSquare )
						{
						for( countSq = (fromSquare + 9); countSq < toSquare; countSq += 9 )
						{
							checkSq = board120[countSq];
							if(  checkSq >= wqR && checkSq <= wPh )
								toColor = WHITE;
							if( checkSq >= bqR && checkSq <= bPh )
								toColor = BLACK;
							else toColor = EMPTY;
							if( checkSq == toSquare )
							{
								return true;
								break;
							}
					
							if( toColor == side )
							{	
								cout << "Invalid move. Queen can't move through it's own piece." << endl;
								return false;
							}
						
							if( checkSq == -1 )
							{
								cout << "Invalid move." << endl;
								return false;
							}
			
								
							if( checkSq >= wqR && checkSq <= bPh )
							{
								cout << "Invalid move. Queen can't move through pieces." << endl;
								return false;
							}	
						}
				}	
						if( toSquare < fromSquare )
						{	
							for( countSq = (fromSquare - 9); countSq > toSquare; countSq -= 9 )
							{
								checkSq = board120[countSq];
								if( checkSq >= wqR && checkSq <= wPh )
									toColor = WHITE;
								if( checkSq >= bqR && checkSq <= bPh )
									toColor = BLACK;
								else toColor = EMPTY;
								if( checkSq == toSquare )
								{
									return true;
								}
						
								if( toColor == side )
								{
									cout << "Invalid move. Queen can't move through it's own piece." << endl;
									return false;
								}
						
								if( checkSq == -1 )
								{	
									cout << "Invalid move." << endl;
									return false;
								}

								if( checkSq >= wqR && checkSq <= bPh )
								{
									cout << "Invalid move. Queen can't move through pieces." << endl;
									return false;
								}
							}
						}
								

							}
						}	
			else if( difference != 0 )
			{
				if( toSquare > fromSquare )
				{
					for( countSq = (fromSquare + 1); countSq < toSquare; countSq += 1 )
					{
						checkSq = board120[countSq];
						if(  checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == toSquare )
						{
							return true;
							break;
						}
				
						if( toColor == side )
						{	
							cout << "Invalid move. Queen can't move through it's own piece." << endl;
							return false;
						}
					
						if( checkSq == -1 )
						{
							cout << "Invalid move." << endl;
							return false;
						}
		
							
						if( checkSq >= wqR && checkSq <= bPh )
						{
							cout << "Invalid move. Queen can't move through pieces." << endl;
							return false;
						}	
					}
			}	
					if( toSquare < fromSquare )
					{	
						for( countSq = (fromSquare - 1); countSq > toSquare; countSq -= 1 )
						{
							checkSq = board120[countSq];
							if( checkSq >= wqR && checkSq <= wPh )
								toColor = WHITE;
							if( checkSq >= bqR && checkSq <= bPh )
								toColor = BLACK;
							else toColor = EMPTY;
							if( checkSq == toSquare )
							{
								return true;
							}
					
							if( toColor == side )
							{
								cout << "Invalid move. Queen can't move through it's own piece." << endl;
								return false;
							}
					
							if( checkSq == -1 )
							{	
								cout << "Invalid move."  << endl;
								return false;
							}

							if( checkSq >= wqR && checkSq <= bPh )
							{
								cout << "Invalid move. Queen can't move through pieces." << endl;
								return false;
							}
						}
					}
			}
		}
		}
			
		}
	
	if( pieceType == KING )
	{
		int valid;
		int countSq;
		int index;
		int checkSq;
		int count = 0;
		int difference = 0;
		int opposite = !side;	
	
		int check;
		check = (toSquare - fromSquare);
		difference = abs(check);	
		if( difference > 11 )
		{
			cout << "Invalid move." << endl;
			return false;
		}
	
		//If king movement is vertical.
		difference = ((toSquare - fromSquare) % 10 );
		if( difference == 0 )	
		{
			if( toSquare > fromSquare )
			{
				for( countSq = (fromSquare + 10); countSq < toSquare; countSq += 10 )
				{
					checkSq = board120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == toSquare )
					{
						return true;
						break;
					}
			
					if( toColor == side )
					{	
						cout << "Invalid move. Rook can't move through it's own piece." << endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						cout << "Invalid move. Offboard square." << endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						cout << "Invalid move. Rook can't move through pieces." << endl;
						return false;
					}	
				}
		}	
				if( toSquare < fromSquare )
				{	
					for( countSq = (fromSquare - 10); countSq > toSquare; countSq -= 10 )
					{
						checkSq = board120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == toSquare )
						{
							return true;
						}
				
						if( toColor == side )
						{
							cout << "Invalid move. Rook can't move through it's own piece." << endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							cout << "Invalid move. Offboard square." << endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							cout << "Invalid move. Rook can't move through pieces." << endl;
							return false;
						}
					}
				}
		}
		else if( difference != 0 )
		{
			difference = (toSquare - fromSquare) % 11;
			if( difference == 0 )
			{
			if( toSquare > fromSquare )
			{
				for( countSq = (fromSquare + 11); countSq < toSquare; countSq += 11 )
				{
					checkSq = board120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == toSquare )
					{
						return true;
						break;
					}
			
					if( toColor == side )
					{	
						cout << "Invalid move. Bishop can't move through it's own piece." << endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						cout << "Invalid move. Offboard square." << endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						cout << "Invalid move. Bishop can't move through pieces." << endl;
						return false;
					}	
				}
			}	
				if( toSquare < fromSquare )
				{	
					for( countSq = (fromSquare - 11); countSq > toSquare; countSq -= 11 )
					{
						checkSq = board120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == toSquare )
						{
							return true;
						}
				
						if( toColor == side )
						{
							cout << "Invalid move. Bishop can't move through it's own piece." << endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							cout << "Invalid move. Offboard square." << endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							cout << "Invalid move. Bishop can't move through pieces." << endl;
							return false;
						}
					}
				}
				}
				else if( difference != 0 )
				{
					int checkDifference;
					difference = (toSquare - fromSquare) % 9;
					checkDifference = difference;
					if( difference == 0 )
					{
						if( checkDifference == 0 )
						{
						if( toSquare > fromSquare )
						{
						for( countSq = (fromSquare + 9); countSq < toSquare; countSq += 9 )
						{
							checkSq = board120[countSq];
							if(  checkSq >= wqR && checkSq <= wPh )
								toColor = WHITE;
							if( checkSq >= bqR && checkSq <= bPh )
								toColor = BLACK;
							else toColor = EMPTY;
							if( checkSq == toSquare )
							{
								return true;
								break;
							}
					
							if( toColor == side )
							{	
								cout << "Invalid move. Bishop can't move through it's own piece." << endl;
								return false;
							}
						
							if( checkSq == -1 )
							{
								cout << "Invalid move. Offboard square." << endl;
								return false;
							}
			
								
							if( checkSq >= wqR && checkSq <= bPh )
							{
								cout << "Invalid move. Bishop can't move through pieces." << endl;
								return false;
							}	
						}
				}	
						if( toSquare < fromSquare )
						{	
							for( countSq = (fromSquare - 9); countSq > toSquare; countSq -= 9 )
							{
								checkSq = board120[countSq];
								if( checkSq >= wqR && checkSq <= wPh )
									toColor = WHITE;
								if( checkSq >= bqR && checkSq <= bPh )
									toColor = BLACK;
								else toColor = EMPTY;
								if( checkSq == toSquare )
								{
									return true;
								}
						
								if( toColor == side )
								{
									cout << "Invalid move. Bishop can't move through it's own piece." << endl;
									return false;
								}
						
								if( checkSq == -1 )
								{	
									cout << "Invalid move. Offboard square." << endl;
									return false;
								}

								if( checkSq >= wqR && checkSq <= bPh )
								{
									cout << "Invalid move. Bishop can't move through pieces." << endl;
									return false;
								}
							}
						}
								

							}
						}	
			else if( difference != 0 )
			{
				if( toSquare > fromSquare )
				{
					for( countSq = (fromSquare + 1); countSq < toSquare; countSq += 1 )
					{
						checkSq = board120[countSq];
						if(  checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == toSquare )
						{
							return true;
							break;
						}
				
						if( toColor == side )
						{	
							cout << "Invalid move. Rook can't move through it's own piece." << endl;
							return false;
						}
					
						if( checkSq == -1 )
						{
							cout << "Invalid move. Offboard square." << endl;
							return false;
						}
		
							
						if( checkSq >= wqR && checkSq <= bPh )
						{
							cout << "Invalid move. Rook can't move through pieces." << endl;
							return false;
						}	
					}
			}	
					if( toSquare < fromSquare )
					{	
						for( countSq = (fromSquare - 1); countSq > toSquare; countSq -= 1 )
						{
							checkSq = board120[countSq];
							if( checkSq >= wqR && checkSq <= wPh )
								toColor = WHITE;
							if( checkSq >= bqR && checkSq <= bPh )
								toColor = BLACK;
							else toColor = EMPTY;
							if( checkSq == toSquare )
							{
								return true;
							}
					
							if( toColor == side )
							{
								cout << "Invalid move. Rook can't move through it's own piece." << endl;
								return false;
							}
					
							if( checkSq == -1 )
							{	
								cout << "Invalid move. Offboard square." << endl;
								return false;
							}

							if( checkSq >= wqR && checkSq <= bPh )
							{
								cout << "Invalid move. Rook can't move through pieces." << endl;
								return false;
							}
						}
					}
			}
		}
		}
			
		}
	

		
	if( pieceType == PAWN )
	{
		int index;
		int toColor;
		int check;
		int checkSq;
		int checkPiece;
		int difference;
		int piece;
		int toPiece;	
		piece = board120[fromSquare];
		toPiece = board120[toSquare];

		/* Take absolute value of difference to limit legal pawn moves */
		difference = abs(toSquare - fromSquare);

		/* Simple check if pawns are trying to move backwards */
		if(( toSquare < fromSquare) && pieceColor == WHITE )
		{
			cout << "Pawns can't move backwards." << endl;
			return false;	
		}
		if(( toSquare > fromSquare) && pieceColor == BLACK )
		{
			cout << "Pawns can't move backwards." << endl;
			return false;
		}
		
		/* Checks the color of the square pawns are moving to. */	
		if( toPiece >= wqR && toPiece <= wPh )
			toColor = WHITE;

		if( toPiece >= bqR && toPiece <= bPh )
			toColor = BLACK;
	
		if( toPiece == 0 )
			toColor = EMPTY;
	
		if( toPiece == -1 )
			toColor = OFFBOARD;
		
		/* Negates OFFBOARD SQUARES */
		if( toColor == OFFBOARD )
		{
			cout << "Invalid move. Can't move offboard." << endl;
			return false;
		}

		/* Negates any pawn moves not forward, captures, or first move 2 squares */
		if( ( difference > 11 || difference < 9 )  && ( difference != 20 ) )
		{
			cout << "Invalid move." << endl;
			return false;
		}
		
		/* Negates forward captures */
		if( difference == 10 && toColor != EMPTY )
		{
			cout << "Pawns can't capture forwards." << endl;
			return false;
		}		
		
		/* Legal move! */
		if( difference == 10 && toColor == EMPTY )
		{
			return true;
		}

		/* Legal capture */
		if( ( difference == 9 || difference == 11 ) && ( ( toColor != side ) && ( toColor != EMPTY ) ) )
		{
			return true;
		} 
		
		/* Legalizes two squares on first pawn move */
		if( ( difference == 20 && toColor == EMPTY ) && ( ( fromSquare >= 31 && fromSquare <= 38 ) || ( fromSquare >= 81 && fromSquare <= 88 ) ) )
		{	
			if( side == WHITE )
			{
				for( checkSq = (fromSquare + 10); checkSq < toSquare; checkSq += 10 )
				{
					checkPiece = board120[checkSq];
					if( checkPiece != 0 )
					{
						cout << "Invalid move." << endl;
						return false;
					}
				}
				return true;
			}
			if( side == BLACK )
			{
				for( checkSq = (fromSquare - 10); checkSq > toSquare; checkSq -= 10 )
				{
					checkPiece = board120[checkSq];
					if( checkPiece != 0 )
					{
						cout << "Invalid move." << endl;
						return false;
					}
				}
				return true;
			}
		}

		/* Negates diagonal pawn move without capture */
		if( ( difference == 9 || difference == 11 ) && toColor == EMPTY )
		{
			return false;
		}
	
		/* Negates two square capture */
		if ( difference == 20 && toColor != EMPTY )
			return false;
		
		/* Negates two square move on anything except first row */
		if( difference == 20 && (fromSquare > 38 && fromSquare < 81) )
		{
			cout << "Invalid move. Can't move two squares if not on first row." << endl;
			return false;
		}
	}


		
	return true;

}

bool checkCheck()
{
	int wKsquare;
	int bKsquare;
	int countSq;
	int piece;
	int toColor;
	int inCheck;
	int index;
	int checkPiece;
	int knightLegal[8];

	wKsquare = pieceList[wK].position;
	bKsquare = pieceList[bK].position;

	do
	{
		/* Check for attackers in every direction */
		for( countSq = (wKsquare - 1); countSq != -1; countSq-- )
		{
			piece = board120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieceList[piece].color == side )
					break;			
				else
				{
					if( pieceList[piece].type == ROOK || pieceList[piece].type == QUEEN )
					{
						cout << "King is in check!" << endl;
						inCheck = true;
					} 	
				}	
			}
		} 

		for( countSq = (wKsquare + 1); countSq != -1; countSq++ )
		{	
			piece = board120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieceList[piece].color == side )
					break;			
				else
				{
					if( pieceList[piece].type == ROOK || pieceList[piece].type == QUEEN )
					{
						cout << "King is in check!" << endl;
						inCheck = true;
					} 	
				}	
			}
		} 

		for( countSq = (wKsquare + 10); countSq != -1; countSq += 10 )
		{	
			piece = board120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieceList[piece].color == side )
					break;			
				else
				{
					if( pieceList[piece].type == ROOK || pieceList[piece].type == QUEEN )
					{
						cout << "King is in check!" << endl;
						inCheck = true;
					} 	
				}	
			}
		} 
		
		for( countSq = (wKsquare - 1); countSq != -1; countSq -- )
		{	
			piece = board120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieceList[piece].color == side )
					break;			
				else
				{
					if( pieceList[piece].type == ROOK || pieceList[piece].type == QUEEN )
					{
						cout << "King is in check!" << endl;
						inCheck = true;
					} 	
				}	
			}
		} 
		
		for( countSq = (wKsquare + 11); countSq != -1; countSq += 11 )
		{	
			piece = board120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieceList[piece].color == side )
					break;			
				else
				{
					if( pieceList[piece].type == BISHOP || pieceList[piece].type == QUEEN )
					{
						cout << "King is in check!" << endl;
						inCheck = true;
					} 	
				}	
			}
		} 
			
		for( countSq = (wKsquare - 1); countSq != -1; countSq -= 11 )
		{	
			piece = board120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieceList[piece].color == side )
					break;			
				else
				{
					if( pieceList[piece].type == BISHOP || pieceList[piece].type == QUEEN )
					{
						cout << "King is in check!" << endl;
						inCheck = true;
					} 	
				}	
			}
		} 
		
		for( countSq = (wKsquare + 9); countSq != -1; countSq += 9 )
		{	
			piece = board120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieceList[piece].color == side )
					break;			
				else
				{
					if( pieceList[piece].type == BISHOP || pieceList[piece].type == QUEEN )
					{
						cout << "King is in check!" << endl;
						inCheck = true;
					} 	
				}	
			}
		} 
	
		for( countSq = (wKsquare - 9); countSq != -1; countSq -= 9 )
		{	
			piece = board120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieceList[piece].color == side )
					break;			
				else
				{
					if( pieceList[piece].type == BISHOP || pieceList[piece].type == QUEEN )
					{
						cout << "King is in check!" << endl;
						inCheck = true;
					} 	
				}	
			}
		} 
		
		/* Check for knight check separately */

		knightLegal[0] = (wKsquare - 21);
		knightLegal[1] = (wKsquare - 19);
		knightLegal[2] = (wKsquare - 12);
		knightLegal[3] = (wKsquare -  8);
		knightLegal[4] = (wKsquare +  8);
		knightLegal[5] = (wKsquare + 12); 
		knightLegal[6] = (wKsquare + 19);
		knightLegal[7] = (wKsquare + 21);
		
		int checkPiece;
		for( index = 0; index < 8; index++ )
		{
			checkPiece = knightLegal[index];
			if( pieceList[checkPiece].color != side && pieceList[checkPiece].type == KNIGHT )
			{
				cout << "King is in check!" << endl;
				inCheck = true;
				return true;
			}
		}	
	} while( !inCheck && side == WHITE );	
	
	do
	{

	for( countSq = (bKsquare - 1); countSq != -1; countSq-- )
	{
		piece = board120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieceList[piece].color == side )
				break;			
			else
			{
				if( pieceList[piece].type == ROOK || pieceList[piece].type == QUEEN )
				{
					cout << "King is in check!" << endl;
					inCheck = true;
				} 	
			}	
		}
	} 

	for( countSq = (bKsquare + 1); countSq != -1; countSq++ )
	{	
		piece = board120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieceList[piece].color == side )
				break;			
			else
			{
				if( pieceList[piece].type == ROOK || pieceList[piece].type == QUEEN )
				{
					cout << "King is in check!" << endl;
					inCheck = true;
				} 	
			}	
		}
	} 

	for( countSq = (bKsquare + 10); countSq != -1; countSq += 10 )
	{	
		piece = board120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieceList[piece].color == side )
				break;			
			else
			{
				if( pieceList[piece].type == ROOK || pieceList[piece].type == QUEEN )
				{
					cout << "King is in check!" << endl;
					inCheck = true;
				} 	
			}	
		}
	} 
	
	for( countSq = (bKsquare - 1); countSq != -1; countSq -- )
	{	
		piece = board120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieceList[piece].color == side )
				break;			
			else
			{
				if( pieceList[piece].type == ROOK || pieceList[piece].type == QUEEN )
				{
					cout << "King is in check!" << endl;
					inCheck = true;
				} 	
			}	
		}
	} 
	
	for( countSq = (bKsquare + 11); countSq != -1; countSq += 11 )
	{	
		piece = board120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieceList[piece].color == side )
				break;			
			else
			{
				if( pieceList[piece].type == BISHOP || pieceList[piece].type == QUEEN )
				{
					cout << "King is in check!" << endl;
					inCheck = true;
				} 	
			}	
		}
	} 
		
	for( countSq = (bKsquare - 1); countSq != -1; countSq -= 11 )
	{	
		piece = board120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieceList[piece].color == side )
				break;			
			else
			{
				if( pieceList[piece].type == BISHOP || pieceList[piece].type == QUEEN )
				{
					cout << "King is in check!" << endl;
					inCheck = true;
				} 	
			}	
		}
	} 
	
	for( countSq = (bKsquare + 9); countSq != -1; countSq += 9 )
	{	
		piece = board120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieceList[piece].color == side )
				break;			
			else
			{
				if( pieceList[piece].type == BISHOP || pieceList[piece].type == QUEEN )
				{
					cout << "King is in check!" << endl;
					inCheck = true;
				} 	
			}	
		}
	} 

	for( countSq = (bKsquare - 9); countSq != -1; countSq -= 9 )
	{	
		piece = board120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieceList[piece].color == side )
				break;			
			else
			{
				if( pieceList[piece].type == BISHOP || pieceList[piece].type == QUEEN )
				{
					cout << "King is in check!" << endl;
					inCheck = true;
				} 	
			}	
		}
	} 
	
	/* Check for knight check separately */

	knightLegal[0] = (bKsquare - 21);
	knightLegal[1] = (bKsquare - 19);
	knightLegal[2] = (bKsquare - 12);
	knightLegal[3] = (bKsquare -  8);
	knightLegal[4] = (bKsquare +  8);
	knightLegal[5] = (bKsquare + 12); 
	knightLegal[6] = (bKsquare + 19);
	knightLegal[7] = (bKsquare + 21);
	
	for( index = 0; index < 8; index++ )
	{
		checkPiece = knightLegal[index];
		if( pieceList[checkPiece].color != side && pieceList[checkPiece].type == KNIGHT )
		{
			cout << "King is in check!" << endl;
			inCheck = true;
			return true;
		}
	}	
	
	

	} while(!inCheck && side == BLACK);

	if( inCheck )
		return true;
	if( !inCheck )
		return false;	
	return false;
}

void legalMoves()
{
		
}

