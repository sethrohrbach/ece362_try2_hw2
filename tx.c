/*
tx.c - this program will fork two processes to run xor and twist programs, also written with this assignment,
such that the output of twist is sent through a unix pipe to xor
For Portland State University ECE362 Winter 2020
Author: Seth Rohrbach
Last Modified: Jan 22, 2020

----------------------------
expected arguments:
-i <filename> : input file name. default is stdin. this argument will be sent to twist.
-o <filename> : output file name. default is stdout. this argument will be sent to xor.
-b <num>      : number of characters in a block to reverse. default is 10. this argument will be sent to twist.
<string>      : mask used. must be less than 10 chars. this argument is mandatory and there is no default. this program will be sent to xor.

TODO:

-parse input
-will probably need additional logic to insure a mask string is provided.

-handle system call to fork two processes

-handle system calls to pipe data between the two programs

-send arguments to twist and xor

-handle system calls for input and output


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


  
  return 0;
}
