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

  int i = 0;

  int fd_out = STDOUT_FILENO;
  int fd_in = STDIN_FILENO;
  char file_buf[1024];
  char mask[11];
  bool mask_rcv = false;
  int mask_len;

  int bytes_read;

  //Parse input, open files, and assign mask.
  for (i = 1; i < argc; i++)
  {
    //printf("looking at argc[%d] = %s", i, argv[i]);
    if (!(strcmp(argv[i], "-i")))
    {
      fd_in = open(argv[i+1], O_RDONLY, 0644);
      if (fd_in < 0)
      {
        char input_error[50];
        strcpy(input_error, "ERROR opening input file. Does it exist?");
        write(STDERR_FILENO, input_error, strlen(input_error));
        return -1;
      }
      i++;
    }
    else if (!(strcmp(argv[i], "-o")))
    {
      fd_out = open(argv[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (fd_out < 0)
      {
        char output_error[50];
        strcpy(output_error, "ERROR opening output file.");
        write(STDERR_FILENO, output_error, strlen(output_error));
        return -1;
      }
      i++;
    }
    else //Else it better be the mask.. no way to positively ID it. If we get more than 1 garbage entry will abort tho.
    {
      if (strlen(argv[i]) > 11) //If it's too long, we are gonna error out.
      {
        char bad_mask[60];
        strcpy(bad_mask, "Bad entry. Mask must be less than 10 chars.");
        write(STDERR_FILENO, bad_mask, strlen(bad_mask));
        return -1;
      }
      else //Else we're gonna check if we've already got one mask. Maybe multiple garbage inputs. If so error out.
      {
        if (mask_rcv == true)
        {
            char more_garb[200];
            strcpy(more_garb, "Too many invalid entries. Usage: xor <mask> -i <filename> -o <filename>. Mask argument must be included. Mask must be less than 10 chars.");
            write(STDERR_FILENO, more_garb, strlen(more_garb));
        }
        else //Else it's probably the mask. Can't positively identify it but its passed the checks so we'll take it.
        {
        strcpy(mask, argv[i]);
        mask_rcv = true;
        mask_len = strlen(mask);
        //write(STDERR_FILENO, mask, strlen(mask));
        }
      }
    }
  }
  //Error out if no mask, should only be if no args included.
  if (!mask_rcv)
  {
    char no_mask[60];
    strcpy(no_mask, "No mask argument found. Mask argument must be included.");
    write(STDERR_FILENO, no_mask, strlen(no_mask));
    return -1;
  }

//Read the file, XOR it, write the file.

char xor_res;

while ((bytes_read = read(fd_in, file_buf, mask_len)) != 0)
{
  i = 0;
  //write(STDERR_FILENO, file_buf, bytes_read);
  //write(STDERR_FILENO, "\t\t", 4);
  //write(STDERR_FILENO, &bytes_read, sizeof(bytes_read));
  while (i < bytes_read)
  {
    //write(STDERR_FILENO, "index = ", 20);
    //write(STDERR_FILENO, &i, sizeof(i));
    xor_res = file_buf[i] ^ mask[i];
    write(fd_out, &xor_res, 1);
    i++;
  }
  //write(STDERR_FILENO, "Reading file...", 30);
}

  return 0;
}
