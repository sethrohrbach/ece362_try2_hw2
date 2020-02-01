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

  int i = 0;
  int b_val = 10;

  int fd_out = STDOUT_FILENO;
  int fd_in = STDIN_FILENO;
  char file_buf[1024];
  char mask[11];

  int bytes_read;

  //Parse input, open files, and assign mask.
  for (i = 1; i < argc; i++)
  {
    //printf("looking at argc[%d] = %s", i, argv[i]);
    if (!(strcmp(argv[i], "-i")))
    {
      fd_in = open(argv[i+1], O_RDONLY, 0644);
      i++;
    }
    else if (!(strcmp(argv[i], "-o")))
    {
      fd_out = open(argv[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
      i++;
    }
    else if (!(strcmp(argv[i], "-b")))
    {
      b_val = atoi(argv[i+1]);
      if (b_val > 1024)
      {
        char b_error[40];
        strcpy(b_error, "Block value must be less than 1024.\n");
        write(STDERR_FILENO, b_error, strlen(b_error));
        return -1;
      }
    }
    else
    {
      char bad_entry[100];
      strcpy(bad_entry, "Invalid entry. Expected arguments: -i <filename> -o <filename> -b <int>\n");
      write(STDERR_FILENO, bad_entry, strlen(bad_entry));
      return -1;
    }

  }


  return 0;
}
