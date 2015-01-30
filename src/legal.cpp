/*
 *	Collider 0.01 Chess Engine
 *	legal.cpp	
 *  Holds all functions involved in checking legality of moves.
 *
 *
 */

#include <iostream>
#include "primer.h"
#include "legal.h"

/* Check if the user or cpu move is legal */
bool checkLegal(boardStruct &board, bool &stop)
{
	int piece, pieceType, pieceColor, toColor, toValue;
	piece = board.sq120[board.frSq];
	toValue = board.sq120[board.toSq];
	
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
	if(( board.side == WHITE) && (pieceColor == BLACK) )
	{
		std::cout << "Invalid move. White to move. " << std::endl;
		return false;
	}
	
	else if(( board.side == BLACK) && (pieceColor == WHITE))
	{
		std::cout << "Invalid move. Black to move." << std::endl;
		return false;
	}
	
	if( piece == NONE )
	{
		std::cout << "Invalid move. Empty square." << std::endl;
		return false;
	}
	
	if( toColor == board.side ) 
	{
		std::cout << "Invalid move. Don't take your own piece." << std::endl;
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

		knightLegal[0] = (board.frSq - 21);
		knightLegal[1] = (board.frSq - 19);
		knightLegal[2] = (board.frSq - 12);
		knightLegal[3] = (board.frSq -  8);
		knightLegal[4] = (board.frSq +  8);
		knightLegal[5] = (board.frSq + 12);
		knightLegal[6] = (board.frSq + 19);
		knightLegal[7] = (board.frSq + 21);

		for( index = 0; index < 8; index++ )
		{
			if( knightLegal[index] == board.toSq )
				return true;
		}
		
		std::cout << "Invalid move. Knights don't move like that." << std::endl;
		return false;
		
	}
	// Check if rook move is legal.
	if( pieceType == ROOK )
	{
		int countSq;
		int checkSq;
		int difference;
		int checkDifference;
	
		//If rook movement is vertical.
		difference = ((board.toSq - board.frSq) % 10 );
		checkDifference = abs(board.toSq - board.frSq);
	
		if( difference != 0 && (checkDifference > 7) )
		{
			std::cout << "Invalid move. Rooks don't move like that." << std::endl;
			return false;
		}
		if( difference == 0 )	
		{
			if( board.toSq > board.frSq )
			{
				for( countSq = (board.frSq + 10); countSq < board.toSq; countSq += 10 )
				{
					checkSq = board.sq120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == board.toSq )
					{
						return true;
						break;
					}
			
					if( toColor == board.side )
					{	
						std::cout << "Invalid move. Rook can't move through it's own piece." << std::endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						std::cout << "Invalid move. Offboard square." << std::endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						std::cout << "Invalid move. Rook can't move through pieces." << std::endl;
						return false;
					}	
				}
		}	
				if( board.toSq < board.frSq )
				{	
					for( countSq = (board.frSq - 10); countSq > board.toSq; countSq -= 10 )
					{
						checkSq = board.sq120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == board.toSq )
						{
							return true;
						}
				
						if( toColor == board.side )
						{
							std::cout << "Invalid move. Rook can't move through it's own piece." << std::endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							std::cout << "Invalid move. Offboard square." << std::endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							std::cout << "Invalid move. Rook can't move through pieces." << std::endl;
							return false;
						}
					}
				}
		}
		else if( difference != 0 )
		{
			if( board.toSq > board.frSq )
			{
				for( countSq = (board.frSq + 1); countSq < board.toSq; countSq += 1 )
				{
					checkSq = board.sq120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == board.toSq )
					{
						return true;
						break;
					}
			
					if( toColor == board.side )
					{	
						std::cout << "Invalid move. Rook can't move through it's own piece." << std::endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						std::cout << "Invalid move. Offboard square." << std::endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						std::cout << "Invalid move. Rook can't move through pieces." << std::endl;
						return false;
					}	
				}
		}	
				if( board.toSq < board.frSq )
				{	
					for( countSq = (board.frSq - 1); countSq > board.toSq; countSq -= 1 )
					{
						checkSq = board.sq120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == board.toSq )
						{
							return true;
						}
				
						if( toColor == board.side )
						{
							std::cout << "Invalid move. Rook can't move through it's own piece." << std::endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							std::cout << "Invalid move. Offboard square." << std::endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							std::cout << "Invalid move. Rook can't move through pieces." << std::endl;
							return false;
						}
					}
				}
		}
	}
				
	if( pieceType == BISHOP )
	{
		int countSq;
		int checkSq;
		int difference = 0;
		int checkDifference;


		checkDifference = ((board.toSq - board.frSq) % 9 );
		difference = ((board.toSq - board.frSq) % 11 );
	
		/* Negate any move that isn't a diagonal */
		if( difference != 0 && checkDifference != 0 )
		{
			std::cout << "Invalid move. Bishop can't move like that." << std::endl;
			return false;
		}
		
		/* If movement is on the right diagonal then check path */
		if( difference == 0 )	
		{
			if( board.toSq > board.frSq )
			{
				for( countSq = (board.frSq + 11); countSq < board.toSq; countSq += 11 )
				{
					checkSq = board.sq120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == board.toSq )
					{
						return true;
						break;
					}
			
					if( toColor == board.side )
					{	
						std::cout << "Invalid move. Bishop can't move through it's own piece." << std::endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						std::cout << "Invalid move. Offboard square." << std::endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						std::cout << "Invalid move. Bishop can't move through pieces." << std::endl;
						return false;
					}	
				}
			}	
				if( board.toSq < board.frSq )
				{	
					for( countSq = (board.frSq - 11); countSq > board.toSq; countSq -= 11 )
					{
						checkSq = board.sq120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == board.toSq )
						{
							return true;
						}
				
						if( toColor == board.side )
						{
							std::cout << "Invalid move. Bishop can't move through it's own piece." << std::endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							std::cout << "Invalid move. Offboard square." << std::endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							std::cout << "Invalid move. Bishop can't move through pieces." << std::endl;
							return false;
						}
					}
				}
		}
	
		/* If movement is on left diagonal then check path */
		if( checkDifference == 0 )
		{
			if( board.toSq > board.frSq )
			{
				for( countSq = (board.frSq + 9); countSq < board.toSq; countSq += 9 )
				{
					checkSq = board.sq120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == board.toSq )
					{
						return true;
						break;
					}
			
					if( toColor == board.side )
					{	
						std::cout << "Invalid move. Bishop can't move through it's own piece." << std::endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						std::cout << "Invalid move. Offboard square." << std::endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						std::cout << "Invalid move. Bishop can't move through pieces." << std::endl;
						return false;
					}	
				}
			}	
				if( board.toSq < board.frSq )
				{	
					for( countSq = (board.frSq - 9); countSq > board.toSq; countSq -= 9 )
					{
						checkSq = board.sq120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == board.toSq )
						{
							return true;
						}
				
						if( toColor == board.side )
						{
							std::cout << "Invalid move. Bishop can't move through it's own piece." << std::endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							std::cout << "Invalid move. Offboard square." << std::endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							std::cout << "Invalid move. Bishop can't move through pieces." << std::endl;
							return false;
						}
					}
				}
			}
				
		}
	
	
	if( pieceType == QUEEN )
	{
		int countSq;
		int checkSq;
		int difference = 0;
	
		//If queen movement is vertical.
		difference = ((board.toSq - board.frSq) % 10 );
		if( difference == 0 )	
		{
			if( board.toSq > board.frSq )
			{
				for( countSq = (board.frSq + 10); countSq < board.toSq; countSq += 10 )
				{
					checkSq = board.sq120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == board.toSq )
					{
						return true;
						break;
					}
			
					if( toColor == board.side )
					{	
						std::cout << "Invalid move. Queen can't move through it's own piece." << std::endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						std::cout << "Invalid move." << std::endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						std::cout << "Invalid move. Queen can't move through pieces." << std::endl;
						return false;
					}	
				}
		}	
				if( board.toSq < board.frSq )
				{	
					for( countSq = (board.frSq - 10); countSq > board.toSq; countSq -= 10 )
					{
						checkSq = board.sq120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == board.toSq )
						{
							return true;
						}
				
						if( toColor == board.side )
						{
							std::cout << "Invalid move. Queen can't move through it's own piece." << std::endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							std::cout << "Invalid move." << std::endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							std::cout << "Invalid move. Queen can't move through pieces." << std::endl;
							return false;
						}
					}
				}
		}
		else if( difference != 0 )
		{
			difference = (board.toSq - board.frSq) % 11;
			if( difference == 0 )
			{
			if( board.toSq > board.frSq )
			{
				for( countSq = (board.frSq + 11); countSq < board.toSq; countSq += 11 )
				{
					checkSq = board.sq120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == board.toSq )
					{
						return true;
						break;
					}
			
					if( toColor == board.side )
					{	
						std::cout << "Invalid move. Queen can't move through it's own piece." << std::endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						std::cout << "Invalid move." << std::endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						std::cout << "Invalid move. Queen can't move through pieces." << std::endl;
						return false;
					}	
				}
			}	
				if( board.toSq < board.frSq )
				{	
					for( countSq = (board.frSq - 11); countSq > board.toSq; countSq -= 11 )
					{
						checkSq = board.sq120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == board.toSq )
						{
							return true;
						}
				
						if( toColor == board.side )
						{
							std::cout << "Invalid move. Queen can't move through it's own piece." << std::endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							std::cout << "Invalid move." << std::endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							std::cout << "Invalid move. Queen can't move through pieces." << std::endl;
							return false;
						}
					}
				}
				}
				else if( difference != 0 )
				{
					int checkDifference;
					difference = (board.toSq - board.frSq) % 9;
					checkDifference = difference;
					if( difference == 0 )
					{
						if( checkDifference == 0 )
						{
						if( board.toSq > board.frSq )
						{
						for( countSq = (board.frSq + 9); countSq < board.toSq; countSq += 9 )
						{
							checkSq = board.sq120[countSq];
							if(  checkSq >= wqR && checkSq <= wPh )
								toColor = WHITE;
							if( checkSq >= bqR && checkSq <= bPh )
								toColor = BLACK;
							else toColor = EMPTY;
							if( checkSq == board.toSq )
							{
								return true;
								break;
							}
					
							if( toColor == board.side )
							{	
								std::cout << "Invalid move. Queen can't move through it's own piece." << std::endl;
								return false;
							}
						
							if( checkSq == -1 )
							{
								std::cout << "Invalid move." << std::endl;
								return false;
							}
			
								
							if( checkSq >= wqR && checkSq <= bPh )
							{
								std::cout << "Invalid move. Queen can't move through pieces." << std::endl;
								return false;
							}	
						}
				}	
						if( board.toSq < board.frSq )
						{	
							for( countSq = (board.frSq - 9); countSq > board.toSq; countSq -= 9 )
							{
								checkSq = board.sq120[countSq];
								if( checkSq >= wqR && checkSq <= wPh )
									toColor = WHITE;
								if( checkSq >= bqR && checkSq <= bPh )
									toColor = BLACK;
								else toColor = EMPTY;
								if( checkSq == board.toSq )
								{
									return true;
								}
						
								if( toColor == board.side )
								{
									std::cout << "Invalid move. Queen can't move through it's own piece." << std::endl;
									return false;
								}
						
								if( checkSq == -1 )
								{	
									std::cout << "Invalid move." << std::endl;
									return false;
								}

								if( checkSq >= wqR && checkSq <= bPh )
								{
									std::cout << "Invalid move. Queen can't move through pieces." << std::endl;
									return false;
								}
							}
						}
								

							}
						}	
			else if( difference != 0 )
			{
				if( board.toSq > board.frSq )
				{
					for( countSq = (board.frSq + 1); countSq < board.toSq; countSq += 1 )
					{
						checkSq = board.sq120[countSq];
						if(  checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == board.toSq )
						{
							return true;
							break;
						}
				
						if( toColor == board.side )
						{	
							std::cout << "Invalid move. Queen can't move through it's own piece." << std::endl;
							return false;
						}
					
						if( checkSq == -1 )
						{
							std::cout << "Invalid move." << std::endl;
							return false;
						}
		
							
						if( checkSq >= wqR && checkSq <= bPh )
						{
							std::cout << "Invalid move. Queen can't move through pieces." << std::endl;
							return false;
						}	
					}
			}	
					if( board.toSq < board.frSq )
					{	
						for( countSq = (board.frSq - 1); countSq > board.toSq; countSq -= 1 )
						{
							checkSq = board.sq120[countSq];
							if( checkSq >= wqR && checkSq <= wPh )
								toColor = WHITE;
							if( checkSq >= bqR && checkSq <= bPh )
								toColor = BLACK;
							else toColor = EMPTY;
							if( checkSq == board.toSq )
							{
								return true;
							}
					
							if( toColor == board.side )
							{
								std::cout << "Invalid move. Queen can't move through it's own piece." << std::endl;
								return false;
							}
					
							if( checkSq == -1 )
							{	
								std::cout << "Invalid move."  << std::endl;
								return false;
							}

							if( checkSq >= wqR && checkSq <= bPh )
							{
								std::cout << "Invalid move. Queen can't move through pieces." << std::endl;
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
		int countSq;
		int checkSq;
		int difference = 0;
	
		int check;
		check = (board.toSq - board.frSq);
		difference = abs(check);	
		if( difference > 11 )
		{
			std::cout << "Invalid move." << std::endl;
			return false;
		}
	
		//If king movement is vertical.
		difference = ((board.toSq - board.frSq) % 10 );
		if( difference == 0 )	
		{
			if( board.toSq > board.frSq )
			{
				for( countSq = (board.frSq + 10); countSq < board.toSq; countSq += 10 )
				{
					checkSq = board.sq120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == board.toSq )
					{
						return true;
						break;
					}
			
					if( toColor == board.side )
					{	
						std::cout << "Invalid move. Rook can't move through it's own piece." << std::endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						std::cout << "Invalid move. Offboard square." << std::endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						std::cout << "Invalid move. Rook can't move through pieces." << std::endl;
						return false;
					}	
				}
		}	
				if( board.toSq < board.frSq )
				{	
					for( countSq = (board.frSq - 10); countSq > board.toSq; countSq -= 10 )
					{
						checkSq = board.sq120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == board.toSq )
						{
							return true;
						}
				
						if( toColor == board.side )
						{
							std::cout << "Invalid move. Rook can't move through it's own piece." << std::endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							std::cout << "Invalid move. Offboard square." << std::endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							std::cout << "Invalid move. Rook can't move through pieces." << std::endl;
							return false;
						}
					}
				}
		}
		else if( difference != 0 )
		{
			difference = (board.toSq - board.frSq) % 11;
			if( difference == 0 )
			{
			if( board.toSq > board.frSq )
			{
				for( countSq = (board.frSq + 11); countSq < board.toSq; countSq += 11 )
				{
					checkSq = board.sq120[countSq];
					if(  checkSq >= wqR && checkSq <= wPh )
						toColor = WHITE;
					if( checkSq >= bqR && checkSq <= bPh )
						toColor = BLACK;
					else toColor = EMPTY;
					if( checkSq == board.toSq )
					{
						return true;
						break;
					}
			
					if( toColor == board.side )
					{	
						std::cout << "Invalid move. Bishop can't move through it's own piece." << std::endl;
						return false;
					}
				
					if( checkSq == -1 )
					{
						std::cout << "Invalid move. Offboard square." << std::endl;
						return false;
					}
	
						
					if( checkSq >= wqR && checkSq <= bPh )
					{
						std::cout << "Invalid move. Bishop can't move through pieces." << std::endl;
						return false;
					}	
				}
			}	
				if( board.toSq < board.frSq )
				{	
					for( countSq = (board.frSq - 11); countSq > board.toSq; countSq -= 11 )
					{
						checkSq = board.sq120[countSq];
						if( checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == board.toSq )
						{
							return true;
						}
				
						if( toColor == board.side )
						{
							std::cout << "Invalid move. Bishop can't move through it's own piece." << std::endl;
							return false;
						}
				
						if( checkSq == -1 )
						{	
							std::cout << "Invalid move. Offboard square." << std::endl;
							return false;
						}

						if( checkSq >= wqR && checkSq <= bPh )
						{
							std::cout << "Invalid move. Bishop can't move through pieces." << std::endl;
							return false;
						}
					}
				}
				}
				else if( difference != 0 )
				{
					int checkDifference;
					difference = (board.toSq - board.frSq) % 9;
					checkDifference = difference;
					if( difference == 0 )
					{
						if( checkDifference == 0 )
						{
						if( board.toSq > board.frSq )
						{
						for( countSq = (board.frSq + 9); countSq < board.toSq; countSq += 9 )
						{
							checkSq = board.sq120[countSq];
							if(  checkSq >= wqR && checkSq <= wPh )
								toColor = WHITE;
							if( checkSq >= bqR && checkSq <= bPh )
								toColor = BLACK;
							else toColor = EMPTY;
							if( checkSq == board.toSq )
							{
								return true;
								break;
							}
					
							if( toColor == board.side )
							{	
								std::cout << "Invalid move. Bishop can't move through it's own piece." << std::endl;
								return false;
							}
						
							if( checkSq == -1 )
							{
								std::cout << "Invalid move. Offboard square." << std::endl;
								return false;
							}
			
								
							if( checkSq >= wqR && checkSq <= bPh )
							{
								std::cout << "Invalid move. Bishop can't move through pieces." << std::endl;
								return false;
							}	
						}
				}	
						if( board.toSq < board.frSq )
						{	
							for( countSq = (board.frSq - 9); countSq > board.toSq; countSq -= 9 )
							{
								checkSq = board.sq120[countSq];
								if( checkSq >= wqR && checkSq <= wPh )
									toColor = WHITE;
								if( checkSq >= bqR && checkSq <= bPh )
									toColor = BLACK;
								else toColor = EMPTY;
								if( checkSq == board.toSq )
								{
									return true;
								}
						
								if( toColor == board.side )
								{
									std::cout << "Invalid move. Bishop can't move through it's own piece." << std::endl;
									return false;
								}
						
								if( checkSq == -1 )
								{	
									std::cout << "Invalid move. Offboard square." << std::endl;
									return false;
								}

								if( checkSq >= wqR && checkSq <= bPh )
								{
									std::cout << "Invalid move. Bishop can't move through pieces." << std::endl;
									return false;
								}
							}
						}
								

							}
						}	
			else if( difference != 0 )
			{
				if( board.toSq > board.frSq )
				{
					for( countSq = (board.frSq + 1); countSq < board.toSq; countSq += 1 )
					{
						checkSq = board.sq120[countSq];
						if(  checkSq >= wqR && checkSq <= wPh )
							toColor = WHITE;
						if( checkSq >= bqR && checkSq <= bPh )
							toColor = BLACK;
						else toColor = EMPTY;
						if( checkSq == board.toSq )
						{
							return true;
							break;
						}
				
						if( toColor == board.side )
						{	
							std::cout << "Invalid move. Rook can't move through it's own piece." << std::endl;
							return false;
						}
					
						if( checkSq == -1 )
						{
							std::cout << "Invalid move. Offboard square." << std::endl;
							return false;
						}
		
							
						if( checkSq >= wqR && checkSq <= bPh )
						{
							std::cout << "Invalid move. Rook can't move through pieces." << std::endl;
							return false;
						}	
					}
			}	
					if( board.toSq < board.frSq )
					{	
						for( countSq = (board.frSq - 1); countSq > board.toSq; countSq -= 1 )
						{
							checkSq = board.sq120[countSq];
							if( checkSq >= wqR && checkSq <= wPh )
								toColor = WHITE;
							if( checkSq >= bqR && checkSq <= bPh )
								toColor = BLACK;
							else toColor = EMPTY;
							if( checkSq == board.toSq )
							{
								return true;
							}
					
							if( toColor == board.side )
							{
								std::cout << "Invalid move. Rook can't move through it's own piece." << std::endl;
								return false;
							}
					
							if( checkSq == -1 )
							{	
								std::cout << "Invalid move. Offboard square." << std::endl;
								return false;
							}

							if( checkSq >= wqR && checkSq <= bPh )
							{
								std::cout << "Invalid move. Rook can't move through pieces." << std::endl;
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
		int toColor;
		int checkSq;
		int checkPiece;
		int difference;
		int piece;
		int toPiece;	
		piece = board.sq120[board.frSq];
		toPiece = board.sq120[board.toSq];

		/* Take absolute value of difference to limit legal pawn moves */
		difference = abs(board.toSq - board.frSq);

		/* Simple check if pawns are trying to move backwards */
		if(( board.toSq < board.frSq) && pieceColor == WHITE )
		{
			std::cout << "Pawns can't move backwards." << std::endl;
			return false;	
		}
		if(( board.toSq > board.frSq) && pieceColor == BLACK )
		{
			std::cout << "Pawns can't move backwards." << std::endl;
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
			std::cout << "Invalid move. Can't move offboard." << std::endl;
			return false;
		}

		/* Negates any pawn moves not forward, captures, or first move 2 squares */
		if( ( difference > 11 || difference < 9 )  && ( difference != 20 ) )
		{
			std::cout << "Invalid move." << std::endl;
			return false;
		}
		
		/* Negates forward captures */
		if( difference == 10 && toColor != EMPTY )
		{
			std::cout << "Pawns can't capture forwards." << std::endl;
			return false;
		}		
		
		/* Legal move! */
		if( difference == 10 && toColor == EMPTY )
		{
			return true;
		}

		/* Legal capture */
		if( ( difference == 9 || difference == 11 ) && ( ( toColor != board.side ) && ( toColor != EMPTY ) ) )
		{
			return true;
		} 
		
		/* Legalizes two squares on first pawn move */
		if( ( difference == 20 && toColor == EMPTY ) && ( ( board.frSq >= 31 && board.frSq <= 38 ) || ( board.frSq >= 81 && board.frSq <= 88 ) ) )
		{	
			if( board.side == WHITE )
			{
				for( checkSq = (board.frSq + 10); checkSq < board.toSq; checkSq += 10 )
				{
					checkPiece = board.sq120[checkSq];
					if( checkPiece != 0 )
					{
						std::cout << "Invalid move." << std::endl;
						return false;
					}
				}
				return true;
			}
			if( board.side == BLACK )
			{
				for( checkSq = (board.frSq - 10); checkSq > board.toSq; checkSq -= 10 )
				{
					checkPiece = board.sq120[checkSq];
					if( checkPiece != 0 )
					{
						std::cout << "Invalid move." << std::endl;
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
		if( difference == 20 && (board.frSq > 38 && board.frSq < 81) )
		{
			std::cout << "Invalid move. Can't move two squares if not on first row." << std::endl;
			return false;
		}
	}


		
	return true;

}

bool checkCheck(boardStruct &board, pieceStruct pieces[])
{
	int wKsquare;
	int bKsquare;
	int countSq;
	int piece;
	int inCheck;
	int index;
	int checkPiece;
	int knightLegal[8];

	wKsquare = pieces[wK].position;
	bKsquare = pieces[bK].position;

	do
	{
		/* Check for attackers in every direction */
		for( countSq = (wKsquare - 1); countSq != -1; countSq-- )
		{
			piece = board.sq120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieces[piece].color == board.side )
					break;			
				else
				{
					if( pieces[piece].type == ROOK || pieces[piece].type == QUEEN )
					{
						std::cout << "King is in check!" << std::endl;
						inCheck = true;
					} 	
				}	
			}
		} 

		for( countSq = (wKsquare + 1); countSq != -1; countSq++ )
		{	
			piece = board.sq120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieces[piece].color == board.side )
					break;			
				else
				{
					if( pieces[piece].type == ROOK || pieces[piece].type == QUEEN )
					{
						std::cout << "King is in check!" << std::endl;
						inCheck = true;
					} 	
				}	
			}
		} 

		for( countSq = (wKsquare + 10); countSq != -1; countSq += 10 )
		{	
			piece = board.sq120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieces[piece].color == board.side )
					break;			
				else
				{
					if( pieces[piece].type == ROOK || pieces[piece].type == QUEEN )
					{
						std::cout << "King is in check!" << std::endl;
						inCheck = true;
					} 	
				}	
			}
		} 
		
		for( countSq = (wKsquare - 1); countSq != -1; countSq -- )
		{	
			piece = board.sq120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieces[piece].color == board.side )
					break;			
				else
				{
					if( pieces[piece].type == ROOK || pieces[piece].type == QUEEN )
					{
						std::cout << "King is in check!" << std::endl;
						inCheck = true;
					} 	
				}	
			}
		} 
		
		for( countSq = (wKsquare + 11); countSq != -1; countSq += 11 )
		{	
			piece = board.sq120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieces[piece].color == board.side )
					break;			
				else
				{
					if( pieces[piece].type == BISHOP || pieces[piece].type == QUEEN )
					{
						std::cout << "King is in check!" << std::endl;
						inCheck = true;
					} 	
				}	
			}
		} 
			
		for( countSq = (wKsquare - 1); countSq != -1; countSq -= 11 )
		{	
			piece = board.sq120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieces[piece].color == board.side )
					break;			
				else
				{
					if( pieces[piece].type == BISHOP || pieces[piece].type == QUEEN )
					{
						std::cout << "King is in check!" << std::endl;
						inCheck = true;
					} 	
				}	
			}
		} 
		
		for( countSq = (wKsquare + 9); countSq != -1; countSq += 9 )
		{	
			piece = board.sq120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieces[piece].color == board.side )
					break;			
				else
				{
					if( pieces[piece].type == BISHOP || pieces[piece].type == QUEEN )
					{
						std::cout << "King is in check!" << std::endl;
						inCheck = true;
					} 	
				}	
			}
		} 
	
		for( countSq = (wKsquare - 9); countSq != -1; countSq -= 9 )
		{	
			piece = board.sq120[countSq];
			if( piece >= wqR && piece <= bPh )
			{
				if( pieces[piece].color == board.side )
					break;			
				else
				{
					if( pieces[piece].type == BISHOP || pieces[piece].type == QUEEN )
					{
						std::cout << "King is in check!" << std::endl;
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
			if( pieces[checkPiece].color != board.side && pieces[checkPiece].type == KNIGHT )
			{
				std::cout << "King is in check!" << std::endl;
				inCheck = true;
				return true;
			}
		}	
	} while( !inCheck && board.side == WHITE );	
	
	do
	{

	for( countSq = (bKsquare - 1); countSq != -1; countSq-- )
	{
		piece = board.sq120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieces[piece].color == board.side )
				break;			
			else
			{
				if( pieces[piece].type == ROOK || pieces[piece].type == QUEEN )
				{
					std::cout << "King is in check!" << std::endl;
					inCheck = true;
				} 	
			}	
		}
	} 

	for( countSq = (bKsquare + 1); countSq != -1; countSq++ )
	{	
		piece = board.sq120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieces[piece].color == board.side )
				break;			
			else
			{
				if( pieces[piece].type == ROOK || pieces[piece].type == QUEEN )
				{
					std::cout << "King is in check!" << std::endl;
					inCheck = true;
				} 	
			}	
		}
	} 

	for( countSq = (bKsquare + 10); countSq != -1; countSq += 10 )
	{	
		piece = board.sq120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieces[piece].color == board.side )
				break;			
			else
			{
				if( pieces[piece].type == ROOK || pieces[piece].type == QUEEN )
				{
					std::cout << "King is in check!" << std::endl;
					inCheck = true;
				} 	
			}	
		}
	} 
	
	for( countSq = (bKsquare - 1); countSq != -1; countSq -- )
	{	
		piece = board.sq120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieces[piece].color == board.side )
				break;			
			else
			{
				if( pieces[piece].type == ROOK || pieces[piece].type == QUEEN )
				{
					std::cout << "King is in check!" << std::endl;
					inCheck = true;
				} 	
			}	
		}
	} 
	
	for( countSq = (bKsquare + 11); countSq != -1; countSq += 11 )
	{	
		piece = board.sq120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieces[piece].color == board.side )
				break;			
			else
			{
				if( pieces[piece].type == BISHOP || pieces[piece].type == QUEEN )
				{
					std::cout << "King is in check!" << std::endl;
					inCheck = true;
				} 	
			}	
		}
	} 
		
	for( countSq = (bKsquare - 1); countSq != -1; countSq -= 11 )
	{	
		piece = board.sq120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieces[piece].color == board.side )
				break;			
			else
			{
				if( pieces[piece].type == BISHOP || pieces[piece].type == QUEEN )
				{
					std::cout << "King is in check!" << std::endl;
					inCheck = true;
				} 	
			}	
		}
	} 
	
	for( countSq = (bKsquare + 9); countSq != -1; countSq += 9 )
	{	
		piece = board.sq120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieces[piece].color == board.side )
				break;			
			else
			{
				if( pieces[piece].type == BISHOP || pieces[piece].type == QUEEN )
				{
					std::cout << "King is in check!" << std::endl;
					inCheck = true;
				} 	
			}	
		}
	} 

	for( countSq = (bKsquare - 9); countSq != -1; countSq -= 9 )
	{	
		piece = board.sq120[countSq];
		if( piece >= wqR && piece <= bPh )
		{
			if( pieces[piece].color == board.side )
				break;			
			else
			{
				if( pieces[piece].type == BISHOP || pieces[piece].type == QUEEN )
				{
					std::cout << "King is in check!" << std::endl;
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
		if( pieces[checkPiece].color != board.side && pieces[checkPiece].type == KNIGHT )
		{
			std::cout << "King is in check!" << std::endl;
			inCheck = true;
			return true;
		}
	}	
	
	

	} while(!inCheck && board.side == BLACK);

	if( inCheck )
		return true;
	if( !inCheck )
		return false;	
	return false;
}


