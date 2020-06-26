/*
COURSE:        CS 360 Spring 2018
ASSIGNMENT:    1
AUTHOR:        John Karasev
*/

#include <dict.h>
#include <sequence.h>
#include <stdlib.h>
#include <assert.h>


//see dict.h for function descriptions

Dict* newDict(unsigned int hashSize) {

  //allocate memory for a hashtable with size entries
  HashEncode* table = createHash( hashSize );

  //initialize hashtable entry lists to null
  int index = 0;
  while ( index < hashSize ) {
    table[ index ].list = NULL;
    index++;
  }

  //create a hashtable sentinal (dict) that knows the size of the table
  //and where hashtable is located.
  Dict* dict = ( Dict* ) malloc( sizeof ( Dict ) );
  dict->size = hashSize;
  dict->table = table;

  return dict;
}

HashEncode* createHash( int size ) {
  return (HashEncode*) malloc( sizeof( HashEncode ) * size );
}

void deleteDictDeep(Dict* dict) {

  HashEncode* table = dict->table;

  for ( int i = 0; i < dict->size; i++ ) { //free all lists in hashtable
    ListNode* node = table[ i ].list;
    ListNode* temp = NULL;
    while ( node != NULL ) { //free all nodes in list
      temp = node->next;
      deleteSequence( node->key );
      free( node );
      node = temp;
    }
  }

  free( table ); //free table
  free( dict );  //free sentinal

  return;
}

bool searchDict(Dict* dict, Sequence* key, unsigned int* code) {

  //find the correct list to search sequence
  ListNode* entryList = dict->table[ hash ( key, dict->size ) ].list;

  //loop through each node. If one is identical sequence
  //set code to its code and return true.
  while ( entryList != NULL ) {
    if ( identicalSequences ( entryList->key, key ) ) {
      *code = entryList->code;
      return true;
    }
    entryList = entryList->next;
  }

  return false;
}

void insertIntoDict(Dict* dict, Sequence* key, unsigned int code) {

  HashEncode* table = dict->table;

  //create new listnode and update with new values
  ListNode* newListNode = ( ListNode* ) malloc ( sizeof ( ListNode ) );
  newListNode->key = key;
  newListNode->code = code;

  //insert listnode into the correct hashentry list
  int index = hash ( key, dict->size );
  newListNode->next = table[ index ].list;
  table[ index ].list = newListNode;

  return;
}

int hash ( Sequence* key, int size ) {

  //my cheap hash function
  int sum = 0;
  for ( int i = 0; i < key->count; i++ )
  sum += key->word[ i ] * ( i + 1 );
  return sum % size;
}

//probably will implement in phase 2
int bernstein ( Sequence* key, int size ) {
  return 0;
}

void insertInitialCodesEncode( Dict* dict) {
  //insert codes 0-255 of ASCII into hashtable.
  for(int i = 0; i <= 255; i++ )
    insertIntoDict( dict, newSequence( (unsigned char) i ), i );
  return;
}
