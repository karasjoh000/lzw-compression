/*
COURSE:        CS 360 Spring 2018
ASSIGNMENT:    1
AUTHOR:        John Karasev
*/

#include <sequence.h>
#include <bitStream.h>
#include <lzw.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

bool lzwDecode(unsigned int bits, unsigned int maxBits,
  int (*readFunc )(void* context), void* readContext,
  int (*writeFunc)(unsigned char c, void* context), void* writeContext) {


    //table entry that holds sequence
    typedef struct _table_entry {
      Sequence* sequence;
    } TableEntry;

    BitStream* read = openInputBitStream(readFunc, readContext);

    //hash table that will hold sequences keyed by their code.
    TableEntry* table = (TableEntry*) malloc( sizeof( TableEntry ) * ( ( 1 << maxBits ) ) );

    //initialize table, set all entries to NULL.

    for( int i = 0; i <= ( 1 << maxBits ) - 1; i++ )
      table[i].sequence = NULL;

    //insert initial values 0 -> 255 into the table that hold the ASCII.
    for ( int i = 0; i <= 255; i++ )
      table[ i ].sequence = newSequence( (char) i );

    //values for the algorithm see assignment description.
    unsigned int prevCode = 0;
    unsigned int currCode = 0;
    unsigned int tableIndex = 256; //keeps track of the next available spot in hash.
    unsigned char c;
    Sequence* w = NULL;

    /*-----------------------------------------------------------------------------*/
    /*- LZW DECODE ALGORITHM STARTS HERE see assignment description for details. --*/
    /*-----------------------------------------------------------------------------*/

    //if empty file return
    if ( !readInBits( read, bits, &prevCode ) ) //first code is assigned to prevCode
      return true;

		//check if need to increment bits
    if ( bits != maxBits && tableIndex > ( 1 << bits ) - 2 )
      bits++;

    //output Sequence T[previousCode]
    outputSequence( table[ prevCode ].sequence, writeFunc, writeContext );

    //loops until no more codes in file
    while( readInBits( read, bits, &currCode ) ) {

			//check if need to increment bits
      if ( bits != maxBits && tableIndex > ( 1 << bits ) - 2 )
        bits++;

      // if currCode within table then take first char of T[currCode]
      if ( table[ currCode ].sequence != NULL )
        c = table[ currCode ].sequence->word[ 0 ];
      else  //else take first char of T[prevCode]
        c = table[ prevCode ].sequence->word[ 0 ];

      //if table is not full make new sequence w from T[prevCode] appended with c
      //and add w into next entry of table
      if ( table[ ( 1 << maxBits ) - 1 ].sequence == NULL )
        table[ tableIndex++ ].sequence = w = copySequenceAppend( table[ prevCode ].sequence, c );

      //output Sequence T[currCode]
      outputSequence( table[ currCode ].sequence, writeFunc, writeContext );
      prevCode = currCode;

    }
    /*-----------------------------------------------------------------------*/
    /*------------------ END OF DECODE LZW ALGORITHM. -----------------------*/
    /*-----------------------------------------------------------------------*/


    //free memory borrowed for hash
    for( int i = 0; table[ i ].sequence != NULL && i <= ( 1 << maxBits ) - 2; i++ )
      deleteSequence ( table[ i ].sequence );
    //free the extra entry caused from the flushed bits in encode.
    if ( table[ ( 1 << maxBits ) - 1 ].sequence != NULL ) deleteSequence( table[ ( 1 << maxBits ) - 1 ].sequence );
    free( table );
    free( read );


    return true;

  }
