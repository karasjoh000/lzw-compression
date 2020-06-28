# Library for LZW compression  
-------------

run `make lzwLib/liblzw.a` to build the library.  
refer to `src/lzwLib/include/lzw.h` for the interface. 

# Details
----------

Pseudo-code for LZW encoding:  
```
     Initialize dictionary D and insert characters 0 through 255
     as single character sequences, each with their code set to
     their respective character value.
     integer nextCode = 256
     Create a new Sequence W containing the first byte of data
     while (there is still data to be read) {
          Character C = next byte of data from input
          Create a new Sequence X using W appended with C
          if (Sequence X is found in dictionary D) {
               Sequence W is assigned Sequence X
          } else {
          } 
     }
     find Sequence W in dictionary D and   
     output the code assigned to Sequence W
     if (more codes are permitted) then
          insert Sequence X into dictionary D,
               assigning nextCode as its code
          increment nextCode by 1
     Create a new Sequence W with just the character C
          find Sequence W in D and output its assigned code
``` 


Pseudo-code for LZW decoding:  
```
Table T is a table of Sequences, indexed by an integer code. The table must be large enough to hold as many codes as are permitted by the maximum code bit width. Initialize table
T with entries 0 through 255 with each holding a single character Sequence, one entry for each character 0 through 255, respectively.
     integer previousCode gets the first code read from input
     output Sequence T[previousCode]
     while (there are more codes to be read) {
          integer currentCode gets the next code from input
          if currentCode is within Table T, then
               Character C = first character of T[currentCode]
          else
               Character C = first character of T[previousCode]
          if Table T is not full, then
               Sequence W gets a new sequence using
                         T[previousCode] appended with C
               add Sequence W at the next index/code in Table T
          output Sequence T[currentCode]
          previousCode is assigned currentCode
}
```