//input.cpp

#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "primer.h"

using namespace std;

int fromSquare = 0;
int toSquare = 0;
bool stop = 0;

void userEntry()		//Takes input and converts to file, rank.
{
	string input;
	//Display side to move;
	if( side == WHITE )
	{
		cout << "White to move." << endl;
	}
	if( side == BLACK )
	{
		cout << "Black to move." << endl;
	}

	//Prompt and take the users input.
	cout << "Enter your move!" << endl;
	getline( cin, input );

	if( input == "exit" )
	{
		stop = true;
		return;
	}
	//Error check for too many spaces. Will change later for castling and promotions etc.
	if ((int)input.size()!=5)
	{
		cout << "Invalid input." << endl;
	}
	
	//Error check for invalid ranks and files
	if ( (int)input[0] > 105 || (int)input[0] < 97 || (int)input[3] > 105 || (int)input[3] < 97 ) 
	{	
		cout << "Invalid input." << endl;
	}

	if(( (int)input[1] < 49) ||( (int)input[1] > 57) ||( (int)input[4] < 49) ||( (int)input[4] > 57) )
	{
		cout << "Invalid input." << endl;
	}
	nl(9);

	/* Converts the ASCI value of the input into file and rank */	
	fromSquare = FR2SQ(((int)input[0] - 97), ((int)input[1] - 49));
	toSquare   = FR2SQ(((int)input[3] - 97), ((int)input[4] - 49));	
	

/*	 Debug output 
	int index = 0;
	for( index = 0; index < 5; index++)
	{
		if( index == 2 )
			index++;
		cout << input[index] << endl;
	}

	nl(1);
	
	for( index = 0; index <5; index++)
	{
		if( index == 2 )
			index++;
		cout << (int)input[index] << endl;
	}	
*/

}
