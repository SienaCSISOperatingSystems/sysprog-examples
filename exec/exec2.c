/*
  Another little example of an exec system call

  Jim Teresco, Williams College

  CS 432, Spring 2005
*/

#include <stdio.h>
#include <unistd.h>

int main() {
  char *myargv[] = {"ls", "-l", NULL};

  printf("This program (pid=%d) will also magically become ls -l\n", getpid());
  execvp("ls", myargv);
  printf("So this line never executes unless there's an error:\n");
  perror("execvp");
  return 1;
}
