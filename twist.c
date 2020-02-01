/*
twist.c - this program reverses the order of bytes input, and outputs the bytes in reverse order.

For Portland State University ECE362 Winter 2020
Author: Seth Rohrbach
Last Modified: Jan 22, 2020

----------------------------
expected arguments:
-i <filename> : input file name. default is stdin
-o <filename> : output file name. default is stdout
-b <num>      : number of characters in a block to reverse. default is 10

TODO:

- DONE - parse input

- DONE - handle system calls for input and output

- DONE - logic to reverse the order of strings

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

  int bytes_read;

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


  while ((bytes_read = read(fd_in, file_buf, b_val)) != 0)
  {
    i = 0;
    //write(STDERR_FILENO, file_buf, bytes_read);
    //write(STDERR_FILENO, "\t\t", 4);
    //write(STDERR_FILENO, &bytes_read, sizeof(bytes_read));
    while (i < bytes_read)
    {
      //write(STDERR_FILENO, "index = ", 20);
      //write(STDERR_FILENO, &i, sizeof(i));

      //printf("position = %d",b_val - i);
      write(fd_out, &file_buf[bytes_read - i - 1], 1);
      i++;
    }
    //write(STDERR_FILENO, "Reading file...", 30);

  }





  return 0;
}