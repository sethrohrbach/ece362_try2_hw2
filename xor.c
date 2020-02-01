/*
xor.c - this program reads a sequence of bytes and logically bitwise XORs it with a mask.
this program should be reversable i.e. if the output is returned as input with the same mask, the original input is returned.
For Portland State University ECE362 Winter 2020
Author: Seth Rohrbach
Last Modified: Jan 22, 2020

----------------------------
expected arguments:
-i <filename> : input file name. default is stdin
-o <filename> : output file name. default is stdout
<string>      : mask used. must be less than 10 chars. this argument is mandatory and there is no default.

TODO:

- DONE -parse input
- PARTIAL - need more reobust error checking - will probably need additional logic to insure a mask string is provided.

- DONE - handle system calls for input and output

- DONE - logic to bitwise XOR strings with mask

*/



#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>


#include <stdio.h> //For debugging



int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
