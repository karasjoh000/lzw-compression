#include <lzw.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*   Course:    CS 360 Spring 2018
 Assignment:    1
     Author:    John Karasev
 */

 typedef struct _context {
     FILE* file;
 } Context;
 int mywrite(unsigned char, void*);
 int myread(void*);
 char* concat(char*, char*);

 int main(int argc, char * argv[]) {

	 Context* writecontext = (Context*) malloc( sizeof(Context) );
	 Context* readcontext = (Context*) malloc( sizeof(Context) );
	 writecontext->file = fopen( "./tests/largetext.lzw", "w+" );
	 assert(writecontext->file != NULL);
	 readcontext->file = fopen( "./tests/largetext.txt", "r" );
	 assert(readcontext->file != NULL);
	 lzwEncode(16, 16, myread, readcontext, mywrite, writecontext );
	 fclose(writecontext->file);
	 fclose(readcontext->file);
	 free ( writecontext );
	 free ( readcontext );





     writecontext = (Context*) malloc( sizeof(Context) );
     readcontext = (Context*) malloc( sizeof(Context) );
     writecontext->file = fopen( "./deleteme", "w" );
     printf("file opened");
     readcontext->file = fopen( "./tests/largetext.lzw", "r" );
		 printf("I am here!!!\n");
     lzwDecode( 16, 16, myread, readcontext, mywrite, writecontext );
		 printf("I am here!!!\n");
     fclose(writecontext->file);
     fclose(readcontext->file);
     free(readcontext);
     free(writecontext);
 }

 int mywrite( unsigned char c, void* context) {
     FILE* fileptr = ((Context*)context)->file;
     return fputc(c, fileptr);
 }

 int myread( void* context ) {
     FILE* fileptr = ((Context*)context)->file;
     return fgetc(fileptr);
 }
