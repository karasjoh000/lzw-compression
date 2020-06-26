/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHORS:       John Karasev and Dick Lang
 */


#ifndef BITSTREAM_H
#define BITSTREAM_H
#include <stdbool.h>


#define MAX_CODE_BITS   24
#define CHAR_BITS       8

/***********************************************************************

 BitStream:
 ----------

     Module representing the ability to read or write symbols of
     arbitrary bit lengths to/from sources/destinations.  Usually,
     the sources or destinations are files, but any such details are
     hidden by the use of functions and contexts provided by the user.
     A BitStream may support input or output, but not both.  It may
     also include an internal buffer holding bits which have been
     output by user code, but not sent to the destination, or moved
     into the buffer but not yet taken by the user code.  The bit
     length of a symbol (the nBits parameter below) cannot exceed
     24 bits or be less than 8.

     Consider this interface to be a starting point or a suggestion for
     your code design. Modify it as needed, but obey good object-oriented
     design principles.

     Note: In the first part of the LZW assignment, the argument "nBits"
     used below with outputBits() and readInBits() can be assumed to be
     fixed at 16.  This assumption (that all codes are 16 bits) will make
     your first implementation of this module trivial. However, in a
     subsequent assignment, you will be implementing the use of variable
     length bit codes (8-24 bits), so you will want to consider how you
     will eventually enhance your first version.

 ************************************************************************/


// These contents should only be accessed by the methods
// in this module.  Code using this module should not
// directly access or modify BitStream struct contents.
// replace this line with your desired BitStream contents
typedef struct _bitStream {
    void* context; //add buffer for phase two
    bool write;
		unsigned int buffer;
		unsigned int length;
    int (*writeFunc)(unsigned char c, void* context);
    int (*readFunc)(void* context);
} BitStream;


/* opentInputBitStream:
     Create, initialize and return a new incoming BitStream where readFunc is a pointer
     to a function, which when called with context as an argument, returns the next
     byte from a source of data (probably, but not necessarily, a file). */
BitStream* openInputBitStream(int (*readFunc)(void* context), void* context);

/* openOutputBitStream:
     Create, initialize and return a new outgoing BitStream where writeFunc is a pointer to a
     function, which when called with the character c and context as arguments, writes the
     character c to the data destination (probably, but not necessarily, a file). */
BitStream* openOutputBitStream(int (*writeFunc)(unsigned char c, void* context),void* context);

/* closeAndDeleteBitStream:
     Terminate BitStream bs.  If it is an outgoing BitStream, send any unsent data to the
     destination. Free any heap memory held by the bs. */
void closeAndDeleteBitStream(BitStream* bs);

/* outputBits:
     Output nBits of the integer "code" to the destination.  (The nBits are always the least
     significant nBits of the 32-bit unsigned int code.) It may be that some or all of
     the data are not immediately written to the destination, but could be buffered until
     "pushed out" but subsequent calls to outputBits. The BitStream bs must be an
     output BitStream. */
void outputBits(BitStream* bs, unsigned int nBits, unsigned int  code);

/* readInBits:
     Get the next integer code of length nBits from the input BitStream bs.  If no additional
     code can be obtained from bs, then false is returned.  Otherwise true is returned and
     the *code is set to the code obtained from the input BitStream.  */
bool readInBits(BitStream* bs, unsigned int nBits, unsigned int* code);

#endif
