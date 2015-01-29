#ifndef DISPLAY_H
#define DISPLAY_H
//display.h

//Functions
void displayHeader();
void displayBoard( boardStruct &board );
void displayBitboard( U64 bbDisplay );
int displayGraphics();
void displayAll( boardStruct &board );
void nl( int lines );
void stars( int stars );
void spaces( int spaces );
#endif
