/*
  Another little example of an exec system call

  Jim Teresco, Williams College, Siena College

  CS 432, Spring 2005
  CSIS 330, Fall 2020
*/

#include <stdio.h>
#include <unistd.h>

int main() {
  char *myargv[] = {"ls", "-l", NULL};

  printf("This program (pid=%d) will also magically become ls -l\n", getpid());
  fflush(stdout);
  execvp("ls", myargv);
  printf("So this line never executes unless there's an error:\n");
  perror("execvp");
  return 1;
}
