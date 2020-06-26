/*
COURSE:        CS 360 Spring 2018
ASSIGNMENT:    1
AUTHOR:        John Karasev
*/

#include <stdlib.h>
#include <bitStream.h>


//see bitStream.h for description
BitStream* openInputBitStream(int (*readFunc)(void* context), void* context) {
  BitStream* newInBits = ( BitStream* ) malloc( sizeof( BitStream ) );
  newInBits->write = false;
  newInBits->buffer = 0;
  newInBits->length = 0;
  newInBits->context = context;
  newInBits->readFunc = readFunc;
  newInBits->writeFunc = NULL;
  return newInBits;
}

//see bitStream.h for description
BitStream* openOutputBitStream(int (*writeFunc)(unsigned char c,void* context),void* context) {
  BitStream* newOutBits = ( BitStream* ) malloc( sizeof( BitStream ) );
  newOutBits->write = true;
  newOutBits->context = context;
  newOutBits->writeFunc = writeFunc;
  newOutBits->readFunc = NULL;
  newOutBits->buffer = 0;
  newOutBits->length = 0;
  return newOutBits;
}


void closeAndDeleteBitStream(BitStream* bs) {



  if ( bs->write == true && bs->length != 0 ) {
    //printf("flushing %d bits\n", bs->length);
    bs->writeFunc( bs->buffer << ( 8 - bs->length ), bs->context );
  }

  free( bs );
}

void outputBits(BitStream* bs, unsigned int nBits, unsigned int code) {

	//Make room for nBits LSB.
  bs->buffer = bs->buffer << nBits;
	//Append nBit code to buffer.
  bs->buffer |= code;
	//Keep track of the buffer length.
  bs->length += nBits;

	//while length is more than 7
  while ( bs->length / 8 != 0 ) {
		//move left 8 to output 8 MSB and decrease length by that amount
    int write = bs->buffer >> ( bs->length -= 8);
    bs->writeFunc( write, bs->context );
		//XOR buffer with write bits shifted back into place
		//which clears the 8 MSB in buffer
    bs->buffer ^= ( write << bs->length );
  }

}

bool readInBits(BitStream* bs, unsigned int nBits, unsigned int* code) {
  *code = 0; //Set all bits to 0.

	//When nBits are requested and current buffer length
	//does not have nbits, read into buffer until there are
	//at least nBits in buffer.
  for ( ; bs->length < nBits; bs->length += 8 ) {
    int input = bs->readFunc( bs->context ); //Read 8 bits.
    if ( input == -1 ) return false; //If end of file, quit.
    bs->buffer = ( bs->buffer << 8 ) | input; //make room for 8 bits and append
  }																						//the new 8 bits using OR.

	//assign MSB nBits to code and update length
  *code = bs->buffer >> ( bs->length -= nBits );
	//remove MSB nBits from buffer by using XOR.
  bs->buffer ^= *code << bs->length;
  return true;
}
