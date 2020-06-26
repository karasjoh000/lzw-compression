/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHORS:       John Karasev and Dick Lang
 */

#ifndef DICT_H
#define DICT_H
#include <stdbool.h>
#include "sequence.h"



/***********************************************************************

 Dict:
 -----

     Module representing a dictionary (hash table) for storing and
     retrieving integer symbol codes using a Sequence as a key.

     Dictionaries may be created and deleted.  Sequences can be inserted
     into the dictionary, along with their assigned code.  Sequences can
     be searched for and their code obtained. There is no limit (other
     than available heap memory) to the number of Sequence/code pairs
     that may be stored in a Dictionary.

     Consider this interface to be a starting point or a suggestion for
     your code design. Modify it as needed, but obey good object-oriented
     design principles.

 ***********************************************************************/

//entry in hash table
typedef struct _hash_entry_encode {
	struct _hash_entry_listnode* list; //list with sequences+codes
} HashEncode;

//Sentinal to HashTable
typedef struct _dict {
    int size; //size of hash
    HashEncode* table; //pointer to hash
} Dict;

//linked list that is pointed by
//HashEncode
typedef struct _hash_entry_listnode {
	struct _hash_entry_listnode* next; //next list node
	Sequence* key;
    unsigned int code;
} ListNode;

/*  newDict:
     Create a new Dict with hashSize "buckets" and return a pointer to it */
Dict* newDict(unsigned int hashSize);

/*  createHash:
     Create a hash with size size.  */
HashEncode* createHash(int size);

/*  deleteDictDeep:
     Free dict heap memory along with all of its contents */
void deleteDictDeep(Dict* dict);

/*  searchDict:
     Search dict for key, if found, return true, otherwise false.
     If code is non-null and key is found, set *code to the key's assigned code */
bool searchDict(Dict* dict, Sequence* key, unsigned int* code);

/*  insertIntoDict:
     Insert key into dict and assign code as its associated value.
     (It is assumed that key is NOT already present in dict) */
void insertIntoDict(Dict* dict, Sequence* key, unsigned int  code);

//hash function for the hash.
int hash( Sequence*, int size );

//insert 0-255 ASCII codes into hash.
void insertInitialCodesEncode(Dict* dict);



#endif
