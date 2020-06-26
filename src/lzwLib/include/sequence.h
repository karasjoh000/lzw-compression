/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHORS:       John Karasev and Dick Lang
 */


#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <stdbool.h>

/***********************************************************************

 Sequence:
 ---------

     Module representing character strings of arbritrary length, where
     the characters can be any 8-bit integer value, including zero.

     The module supports creating and deleting sequences, writing them
     to some destination, copying and appending a character and comparing
     them for equality.

     Consider this interface to be a starting point or a suggestion for
     your code design. Modify it as needed, but obey good object-oriented
     design principles.

 ***********************************************************************/

//holds pointer to bytes as well as count
//since null terminator can be part of data
typedef struct _sequence {
    int count; //length of word (not really a word)
    unsigned char* word; //ptr to word
} Sequence;

/* newSequence:
     Create and return a newSequence object with its first and only character equal
     to firstByte. It can be noted that there is no need to support a Sequence that
     has zero characters.  All Sequences used by LZW have at least one character. */
Sequence* newSequence(unsigned char firstByte);

/* deleteSequence:
     Free all heap memory associated with sequence. */
void deleteSequence(Sequence* sequence);

/* copySequenceAppend:
     Create and return a new Sequence object where the new object contains
     all the characters of sequence, but with addByte appended to its end. */
Sequence* copySequenceAppend(Sequence* sequence, unsigned char addByte);

/* outputSequence:
     Write the characters in sequence (in sequential order) using the given
     writeFunc() and its context data. */
void outputSequence(Sequence* sequence,
                    int (*writeFunc)(unsigned char c, void* context), void* context);

/* identicalSequences:
     Return true if a and b contain exactly the same characters in the
     same order, false otherwise. */
bool identicalSequences(Sequence* a, Sequence* b);

//prints sequence to stdout for debugging
void printseq(Sequence* sequence);

#endif
