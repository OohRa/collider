//input.cpp

#include <iostream>
#include "primer.h"
#include "move.h"
#include "input.h"
#include "display.h"
#include "legal.h"

void userEntry(boardStruct &board, bool &stop){		//Takes input and converts to file, rank.
	std::string input;
	//Display side to move;
	if( board.side == WHITE )
	{
		std::cout << "White to move." << std::endl;
	}
	else if( board.side == BLACK )
	{
		std::cout << "Black to move." << std::endl;
	}
	
	else { std::cout << "Nothing!" << std::endl; };
	//Prompt and take the users input.
	std::cout << "Enter your move!" << std::endl;
	getline( std::cin, input );

	if( input == "exit" )
	{
		stop = TRUE;
		return;
	}
	//Error check for too many spaces. Will change later for castling and promotions etc.
	if ((int)input.size()!=5)
	{
		std::cout << "Invalid input." << std::endl;
	}
	
	//Error check for invalid ranks and files
	if ( (int)input[0] > 105 || (int)input[0] < 97 || (int)input[3] > 105 || (int)input[3] < 97 ) 
	{	
		std::cout << "Invalid input." << std::endl;
	}

	if(( (int)input[1] < 49) ||( (int)input[1] > 57) ||( (int)input[4] < 49) ||( (int)input[4] > 57) )
	{
		std::cout << "Invalid input." << std::endl;
	}
	nl(9);

	/* Converts the ASCI value of the input into file and rank */	
	board.frSq = FR2SQ(((int)input[0] - 97), ((int)input[1] - 49));
	board.toSq   = FR2SQ(((int)input[3] - 97), ((int)input[4] - 49));	
	

/*	 Debug output 
	int index = 0;
	for( index = 0; index < 5; index++)
	{
		if( index == 2 )
			index++;
		std::cout << input[index] << std::endl;
	}

	nl(1);
	
	for( index = 0; index <5; index++)
	{
		if( index == 2 )
			index++;
		std::cout << (int)input[index] << std::endl;
	}	
*/

}

void userInput(boardStruct &board, pieceStruct pieces[], bool &stop){
	userEntry(board, stop);
	if( stop ) return;
	while( !checkLegal(board, stop) ){
		displayAll(board);
		userEntry(board, stop);
		if( stop ) return;
	}
	makeMove(board, stop);
//	checkCheck(board, pieces);
	displayAll( board );
}	
