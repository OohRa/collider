//search.h
#ifndef SEARCH_H
#define SEARCH_H

void engine();
int negaMax( int alpha, int beta, int depth );
int quiescence(int alpha = 99999, int beta = -99999);

#endif
