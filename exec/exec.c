/*
  Little example of an exec system call

  Jim Teresco, Williams College

  CS 432, Spring 2005
  CSIS 330, Fall 2020, Siena College
*/

#include <stdio.h>
#include <unistd.h>

int main() {

  printf("This program (pid=%d) will magically become ls -l\n", getpid());
  // the following will force any of the above still buffered and not yet
  // printed to be printed before the execlp, which can cause the output
  // to be lost
  fflush(stdout);
  execlp("ls", "ls", "-l", NULL);
  printf("So this line never executes unless there's an error:\n");
  perror("execlp");
  return 1;
}
