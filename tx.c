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

  //int fd_out = STDOUT_FILENO;
  //int fd_in = STDIN_FILENO;

  //char file_buf[1024];

  char input_file[200];
  char output_file[200];

  char mask[11];
  int mask_len;
  bool mask_rcv = false;
  bool input_rcv = false;
  bool output_rcv = false;

  //int bytes_read;

  //Parse input, open files, and assign b_val and mask.
  for (i = 1; i < argc; i++)
  {
    //printf("looking at argc[%d] = %s", i, argv[i]);
    if (!(strcmp(argv[i], "-i")))
    {
      strcpy(input_file, argv[i+1]);
      input_rcv = true;
      i++;
    }
    else if (!(strcmp(argv[i], "-o")))
    {
      strcpy(output_file, argv[i+1]);
      output_rcv = true;
      i++;
    }
    else if (!(strcmp(argv[i], "-b")))
    {
      b_val = atoi(argv[i+1]);
      i++;
      if (b_val > 1024)
      {
        char b_error[40];
        strcpy(b_error, "Block value must be less than 1024.\n");
        write(STDERR_FILENO, b_error, strlen(b_error));
        return -1;
      }
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

  //Set up the pipe..
  int pipe_st[2];
  pid_t pid;


  if (pipe(pipe_st) < 0)
  {
    char pipe_fail[30];
    strcpy(pipe_fail, "ERROR creating pipe.");
    write(STDERR_FILENO, pipe_fail, strlen(pipe_fail));
  }

  char b_val_string[5];
  sprintf(b_val_string, "%d", b_val);

  pid = fork();

  //write(STDERR_FILENO, &pid, sizeof(pid));

  if (pid == 0) //This is the child
  {
    //wait(NULL);
    //We're making the parent = twist.

    /*
    close(pipe_st[0]);
    close(STDOUT_FILENO);
    dup(pipe_st[1]);
    close(pipe_st[1]);
*/ //Default code..

    // I found dup wasn't reliable, dup2 works better.
    dup2(pipe_st[1], STDOUT_FILENO);
    close(pipe_st[0]);
    close(pipe_st[1]);


    if (input_rcv) //Check if we are sending input args
    {
      execl("twist", "twist", "-i", input_file, "-b", b_val_string, NULL);
      //fprintf(stderr, "Failed to execute twist\n");
    }
    else //else just taking from STDIN.
    {
      execl("twist", "twist", "-b", b_val_string, NULL);
      //fprintf(stderr, "Failed to execute twist\n");
    }

  }
  else if (pid > 0) //This is the parent
  {
    //The child shall be XOR.

/*
    close(pipe_st[1]);
    close(STDIN_FILENO);
    dup(pipe_st[0]); //XOR reads from the pipe.
    close(pipe_st[0]);
    */


    dup2(pipe_st[0], STDIN_FILENO);
    close(pipe_st[1]);
    close(pipe_st[0]);


    if (output_rcv) //Check if we are sending output args
    {
      //write(STDERR_FILENO, "CALLING XOR!", 15);
      execl("./xor", "./xor", mask, "-o", output_file, NULL);
      //fprintf(stderr, "Failed to execute xor\n");

    }
    else //else no output args. STDOUT it is.
    {
      execl("./xor", "./xor", mask, NULL);
      //fprintf(stderr, "Failed to execute xor\n");

    }
  }
  else //Else < 0, this is an error.
  {
    char fork_er[40];
    strcpy(fork_er, "ERROR forking processes.");
    write(STDERR_FILENO, fork_er, strlen(fork_er));
  }

  return 0;
}
