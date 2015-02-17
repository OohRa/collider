//input.cpp

#include <iostream>
#include "primer.h"
#include "move.h"
#include "input.h"
#include "display.h"
#include "legal.h"
#include "board.h"
#include <unistd.h>

//FUE
bool userEntry(){		//Takes input and converts to file, rank.

	std::string input;
	//Display side to move
	if( board.side == WHITE ){
		std::cout << "White to move.\n";
	}
	else if( board.side == BLACK ){
		std::cout << "Black to move.\n";
	}
	
	else { std::cout << "Nothing!" << std::endl; };

	//Prompt and take the users input.
	std::cout << "Enter your move!\n";
	getline( std::cin, input );

	if( input == "exit" ){
		stop = true;
		return false;
	}
	//Allows undo of one move (add multiple moves later when movelists are generated
	if( input == "undo" ){
		std::cout << "Undoing move. Only undo one time!\n";
		unmakeMove();
		changeSide();
		return false;
	}

	//Set castling
	if( input == "o-o" || input == "o-o-o" || input == "0-0" || input == "0-0-0" ){
		board.castling = true;
		board.frSq = ((board.side - 1) * 70) + 25;

		//Set the toSq	
		if( input == "o-o" || input == "0-0" ){
			board.toSq = board.frSq + 1;
		}
		else{
			board.toSq = board.frSq - 1;
		}

		board.oldtoSq = board.toSq;
		board.oldfrSq = board.frSq;
		life++;
		return true;
	}

	//Error check for too many spaces. Will change later for castling and promotions etc.
	else{
		board.castling = false;
		if ((int)input.size()!=5){
			std::cout << "Invalid input.\n";
			return false;
		}
		
		//Error check for invalid ranks and files
		if ( (int)input[0] > 105 || (int)input[0] < 97 || (int)input[3] > 105 || (int)input[3] < 97 ){ 	
			std::cout << "Invalid input.\n";
			return false;
		}

		if(( (int)input[1] < 49) ||( (int)input[1] > 57) ||( (int)input[4] < 49) ||( (int)input[4] > 57) ){
			std::cout << "Invalid input.\n";
			return false;
		}
	}
	nl(9);

	/* Converts the ASCI value of the input into file and rank */	
	board.frSq = FR2SQ(((int)input[0] - 97), ((int)input[1] - 49));
	board.toSq = FR2SQ(((int)input[3] - 97), ((int)input[4] - 49));	
	board.oldfrSq = board.frSq;
	board.oldtoSq = board.toSq;
	return true;
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
	life++;
}

/* Search code (FUI) */
void userInput(){
	getInput();
	if( stop ) return;
	while( !checkLegal() || moveCheck() ){
		displayAll();
		getInput();
		if( stop ) return;
	}	
	
}	

void getInput(){
	while( !userEntry() ){
		if( stop ) return;
		displayAll();
	}
		
	return;
}
