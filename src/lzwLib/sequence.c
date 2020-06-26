/*
COURSE:        CS 360 Spring 2018
ASSIGNMENT:    1
AUTHOR:        John Karasev
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sequence.h>

//see sequence.h for function descriptions

Sequence* newSequence(unsigned char firstByte) {

  Sequence* new = ( Sequence* ) malloc( sizeof( Sequence ) );
  new->word = ( unsigned char* ) ( malloc( sizeof( unsigned char ) ) );
  new->word[0] = firstByte;
  new->count=1;

  return new;
}

void deleteSequence(Sequence* sequence) {
  //free all allocations in sequence
  free(sequence->word);
  free(sequence);
  return;
}

Sequence* copySequenceAppend(Sequence* sequence, unsigned char addByte) {

  Sequence* appended = (Sequence*) malloc(sizeof(Sequence));
  //allocate 1 more than prevous count since appending one byte to it.
  appended->word = ( unsigned char* ) malloc( sizeof( unsigned char ) * ( 1 + sequence->count ) );

  //copy all contents to appended sequence
  for( appended->count = 0; appended->count < sequence->count; appended->count++ )
    appended->word[ appended->count ] = sequence->word[ appended->count ];

  //add the extra byte to appended seq
  appended->word[ appended->count ] = addByte;
  appended->count++;

  return appended;
}

void outputSequence(Sequence* sequence,
  int (*writeFunc)(unsigned char c, void* context), void* context) {

    //output all bytes of sequence
    for( int i = 0; i < sequence->count; i++ )
      writeFunc( sequence->word[i], context );

    return;
  }


  bool identicalSequences(Sequence* a, Sequence* b) {

    //quick check to not compute a lot
    if(a->count != b->count) return false;
    //for each byte check if they are identical.
    for ( int i = 0; i < a->count; i++ )
      if(a->word[i] != b->word[i]) return false;

    return true;
  }

  void printseq(Sequence* sequence) {
    //print sequence to stdout
    for(int i = 0; i < sequence->count; i++ )
      printf("%c", sequence->word[i]);
    printf("\n");
  }
