/*
  Little example of an exec system call

  Jim Teresco, Williams College

  CS 432, Spring 2005
*/

#include <stdio.h>
#include <unistd.h>

int main() {

  printf("This program (pid=%d) will magically become ls -l\n", getpid());
  execlp("ls", "ls", "-l", NULL);
  printf("So this line never executes unless there's an error:\n");
  perror("execlp");
  return 1;
}
