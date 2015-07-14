//search.cpp

#include <iostream>
#include "primer.h"
#include "move.h"
#include "eval.h"
#include "search.h"
#include "board.h"
#include "display.h"
#include "debug.h"
#include "legal.h"
#include <chrono>

int leaf = 0;
int alpha = -99999;
int beta = 99999;
//grandDepth = 7;
void engine(){
	int score, bestMove, bestScore;
	int depth = grandDepth;
	alpha = -99999;
	beta = 99999;
	life = 0;
	score = 0;
	bestScore = alpha;
	bestMove = 0;
/*	
	if( checkCheck() )
		//Remove until implemented cleaning movelist
		//moveGen(board.mL, false, true);
		

	else
		moveGen( board.mL );
*/

	moveGen( board.mL );
	//Time def	
	auto t1 = std::chrono::high_resolution_clock::now();
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;

	//Alpha Beta loop
	for( int i = 0; i < board.mL.size(); i++ ){

		setMove(board.mL, i);

		std::cout << "AlphaBeta move is: ";
		dispMove(board.mL[i]);
		std::cout << "\n";

		makeMove();

		if( checkCheck() ){
			unmakeMove();
			continue;
		}
	
		changeSide();

		//Set the moves to display while the bot searches
		if( slowFlag )
			displayAll();

		//Node incrementer
		life++;	
		

		//Call to negaMax 
		score = -negaMax( -beta, -alpha, depth - 1 );

		if( score > alpha ){
			bestMove = i;
			alpha = score;
			bestScore = score;
			std::cout << "New Best Score!\n";
		}

		std::cout << "AlphaBeta score is: " << score << "\n";
		changeSide();
		unmakeMove();
		
	}
	
	auto t2 = std::chrono::high_resolution_clock::now();
	fsec fs = t2 - t1;
/*
	std::cout << "Depth is: " << depth << "\n";
	if( fs.count() > 30 ){
		std::cout << "Decreasing depth.\n";
		grandDepth--;
	}
	else if( fs.count() < 10 ){
		std::cout << "Increasing depth.\n";
		grandDepth++;
	}
*/	
	//Statistics
	std::cout << std::scientific << "Collider took: "
		  << fs.count()
		  << " seconds\n";
	std::cout << "At "
		  << life / fs.count()
		  << " nodes per seconds\n";
	std::cout << "For a total of: "
		  << life
		  << " nodes\n";
	std::cout << "With " << leaf << " leaves cut!\n";
	leaf = 0;

	std::cout << "Index is: " << bestMove << "\n";
	std::cout << "Depth is " << grandDepth << "\n";
	std::cout << "movelist size is: " << board.mL.size() << "\n";
	std::cout << "The best move is: ";
	dispMove(board.mL[bestMove]);
	nl(1);
	std::cout << "With a score of: " << bestScore << "\n";
	std::cout << "Current score is: ";

	setMove(board.mL, bestMove);
	makeMove();

	//Test for current position check
	if( checkCheck() )
		std::cout << "You're in check man, and you already moved, that's illegal!\n";

	changeSide();

	//Test for current position check
	if( checkCheck() )
		std::cout << "You're in check!\n";

	//debugAll();
	std::cout << -eval() << "\n";
}

int negaMax( int alpha, int beta, int depth ){
	int score;	

	//Think about intializing this vector with a size to increase speed
	std::vector<int> mL;
	mL.reserve(40);

	if( depth == 0 ){
		//score = eval();
		score = quiescence( alpha, beta );
		return score;
	}
	moveGen(mL);

//	debugAll();

	for( int i = 0; i < mL.size(); i++ ){
		setMove(mL, i);
		makeMove();

		if( checkCheck() ){
			unmakeMove();
			continue;
		}

		changeSide();

		if( slowFlag )
			displayAll();
		life++;
		score = -negaMax( -beta, -alpha, depth - 1 );

		changeSide();
		unmakeMove();

		//AlphaBeta pruning
		if( score >= beta ){
			//std::cout << "Leaf pruned!\n";
			leaf++;	
			return beta;
		}
			
		if( score > alpha )
			alpha = score;

	}

	return alpha;
	
}

//Quiescence search
//If captures exist after normal search, continue searching until board is "quiet"
int quiescence(int alpha, int beta){
	int score, base;	
	base = eval();
	if( base >= beta ){
		//std::cout << "Base greater than beta, returning beta: " << beta << "\n";
		return beta;
	}
	if( alpha < base ){
		alpha = base;
		//std::cout << "Alpha less than base, alpha equals base: " << alpha << "\n";
	}
	//changeSide();
	std::vector<int> mL;
	mL.reserve(10);
	//std::cout << "In quiescence search.\n";
	moveGen(mL, true);
	//std::cout << "Searching: " << mL.size() << " moves.\n";
	if( mL.size() == 0 ){
		score = eval();
		//std::cout << "Current score is: " << best << "\n";
		return score;
	}
//	debugAll();
	for( int i = 0; i < mL.size(); i++ ){
		setMove(mL, i);
		makeMove();

		if( checkCheck() ){
			unmakeMove();
			continue;
		}
		changeSide();

			
		if( slowFlag )
			displayAll();
		life++;
		//changeSide();
		score = -quiescence( -beta, -alpha);
		//changeSide();

		changeSide();
		unmakeMove();

		//AlphaBeta pruning
		if( score >= beta ){
			//std::cout << "Leaf pruned!\n";
			leaf++;	
			return beta;
		}
			
		if( score > alpha )
			alpha = score;

	}

	return alpha;
}
