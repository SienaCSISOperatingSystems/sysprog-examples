/*
  Demonstration of perror

  Jim Teresco, Fall 2002, Operating Systems, Williams College
  Updated for Spring 2012, Siena College
*/  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  int fd;
  int retval;

  printf("Attempting to open nonexistent.txt\n");

  fd = open("nonexistent.txt",O_RDONLY);

  /* on failure, open returns -1 and sets errno */
  if (fd == -1) {
    perror("nonexistent.txt");
    fprintf(stderr, "Error number: %d\n", errno);
    exit(1);
  }

  printf("We opened nonexistent.txt.  Misleading filename.\n");

  retval = close(fd);
  /* on failure, open returns -1 and sets errno */
  if (retval == -1) {
    perror("close");
    fprintf(stderr, "Error number: %d\n", errno);
    exit(1);
  }

  return 0;
}
