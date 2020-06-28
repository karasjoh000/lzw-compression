/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHOR:        Dick Lang
 */

#ifndef LZW_H
#define LZW_H
#include <stdbool.h>

/********************************/
/* DO NOT MODIFY THIS INTERFACE */
/********************************/

/* limiting sizes of compression code bits */
#define LZW_MINIMUM_BITS    8
#define LZW_MAXIMUM_BITS    24

/* Introduction:
   ------------

    The interface to lzwEncode() and lzwDecode() utilize the
    following arguments in common:

    unsigned int bits
                The beginning width of symbol codes used in
                the compressed data. Must be >= 8 and <= 24.

    unsigned int maxBits
                The largest number of bits that symbol codes
                are permitted to use.  To successfully decode
                encoded data, these two values (bits & maxBits)'
                must be the same values for decoding as the
                values used for encoding.  Otherwise, decoding
                may fail. Must be >= 8 and <= 24 and >= bits.


    int (*readFunc)(void* context)
                A pointer to a function, which when passed
                a pointer to "context" (see the context
                arguments), will return the next byte of
                input data. If there are no further bytes of
                input data, a -1 is expected to be returned.
                This function pointer must not be NULL.

    int (*writeFunc)(unsigned char c, void* context)
                A pointer to a function which writes the
                character c to the output destination.
                The context pointer (see the last argument)
                is passed to writeFunc() to provide it
                information about where to send the character.
                This function pointer must not be NULL. The
                function returns the character written as
                an int, or returns -1 if there was an error.

    void* readContext, void* writeContext
                Pointers to information about the I/O
                environment of the caller.  The pointers
                are provided as an argument to calls to
                readFunc() and writeFunc() to give those
                functions the information. This argument
                may be NULL, if a NULL argument is suitable
                for readFunc() and writeFunc(). */

/* lzwEncode
   ---------

   Read data using readFunc(), compress it and write the
   compressed data using writeFunc(). Returns true on
   success, false otherwise.  Failures will be due to
   invalid arguments. */

bool lzwEncode(unsigned int bits, unsigned int maxBits,
               int (*readFunc )(void* context), void* readContext,
               int (*writeFunc)(unsigned char c, void* context), void* writeContext);

/* lzwDecode
   ---------

   Read compressed data using readFunc(), decompress it and
   write the decompressed data using writeFunc(). If decompression
   fails, a false result will be returned, otherwise, if it
   succeeds, a true result will be returned.  Failures may be due
   to attempting to decompress uncompressed data, or decompressing
   data that was compressed with different values for bits or
   maxBits. Also, a false result is returned for invalid
   arguments. */

bool lzwDecode(unsigned int bits, unsigned int maxBits,
               int (*readFunc )(void* context), void* readContext,
               int (*writeFunc)(unsigned char c, void* context), void* writeContext);

#endif
