/*
COURSE:        CS 360 Spring 2018
ASSIGNMENT:    1
AUTHOR:        John Karasev
*/

#include <sequence.h>
#include <bitStream.h>
#include <dict.h>
#include <lzw.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


bool lzwEncode(unsigned int bits, unsigned int maxBits, //returns false if parameters are not valid
  int (*readFunc )(void* context), void* readContext,
  int (*writeFunc)(unsigned char c, void* context), void* writeContext) {

    assert( bits >= 8 && maxBits <= 24 );

    BitStream* out = openOutputBitStream(writeFunc, writeContext);

    Dict* dict = newDict( 65537 ); //prime closest to 2^16-1

    insertInitialCodesEncode(dict); //insert 0-255 into dict, see func

    //variables used in algorithm
    unsigned int code; //for searchDict
    unsigned int nextCode = 256; //keep track of code
    unsigned int next; //for next read code
    unsigned char c;
    Sequence* x = NULL;
    Sequence* w = NULL;


    /*-----------------------------------------------------------------------------*/
    /*- LZW ENCODE ALGORITHM STARTS HERE see assignment description for details. --*/
    /*-----------------------------------------------------------------------------*/
    //if EOF return
    if ( ( next = readFunc(readContext) ) == -1) return true;
    //first code assigned to w
    w = newSequence( (unsigned char) next );
    //repeat until EOF
    while ( ( next = readFunc(readContext) ) != -1 ) {

      c = (unsigned char) next;
      x = copySequenceAppend(w, c);

      if ( searchDict( dict, x, &code ) ) {
        deleteSequence( w );
        w = x;
      }
      else {
        searchDict(dict, w, &code);
        outputBits(out, bits, code);

        //check if need to increment bits
        if ( bits != maxBits && nextCode > ( ( 1 << bits ) - 1 ) )
            bits++;

        //if more codes are permitted then insert x into dic
        if ( nextCode <= ( ( 1 << maxBits ) - 1 ) )
          insertIntoDict(dict, x, nextCode++);
        else //else remove x.
          deleteSequence( x );

        deleteSequence( w );
        w = newSequence( c );
      }
    }
    //find Sequence W in dict and output its assigned code
    searchDict(dict, w, &code);
    deleteSequence( w );
    outputBits(out, bits, code);
    closeAndDeleteBitStream ( out );

    /*-----------------------------------------------------------------------*/
    /*------------------ END OF ENCODE LZW ALGORITHM. -----------------------*/
    /*-----------------------------------------------------------------------*/
    //RELEASE ALL MEMORY
    deleteDictDeep( dict );

    return true;
  }
