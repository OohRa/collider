//bitboards.cpp

#include "primer.h"
#include "bitboards.h"

void setBit( int sq, U64 &bbAddress ){
	U64 setBit = 1;
	U64 bb = bbAddress;
	setBit <<= sq;
	bb = bb | setBit;
	bbAddress = bb;
}
 
