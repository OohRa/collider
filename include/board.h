#ifndef BOARD_H
#define BOARD_H
//board.h

int getColor( int sq );
int getType( int sq );
int getPiece( int sq );
int getValue( int sq );
void setMove( std::vector<int>& moveList, int index );

#endif
