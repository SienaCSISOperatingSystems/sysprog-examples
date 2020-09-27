/*
  A dumb little example that reads from a file and writes out
  every other character in that file to a second file

  Jim Teresco, Fall 2002, Operating Systems, Williams College

  Improved March 2005 for better error checking
  Improved error messages, added stdin/stdout options, October 2006
*/

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char buf[3];
  int fd_in, fd_out;

  /* The input file name is specified by argv[1] and the
     output file is specified by argv[2] 

     If only one file is specified, it is assumed to be the 
     input file and stdout is used for output.

     If no files are specified, input is taken from stdin,
     output is directed to stdout.
  */

  if (argc < 2) {
    fd_in = 0;
  }
  else {
    fd_in = open(argv[1], O_RDONLY);
    if (fd_in == -1) {
      perror("open (in)");
      exit(1);
    }
  }

  if (argc < 3) {
    fd_out = 1;
  }
  else {
    fd_out = open(argv[2], O_WRONLY|O_CREAT, 0644);
    if (fd_out == -1) {
      perror("open (out)");
      exit(1);
    }
  }

  while (read(fd_in, buf, 2)) {
    write(fd_out, buf, 1);
  }

  if (close(fd_in) == -1) {
    perror("close (in)");
    exit(1);
  }
  if (close(fd_out) == -1) {
    perror("close (out)");
    exit(1);
  }
  return 0;
}
