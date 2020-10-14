/*
  Little example of an exec system call that takes parameters

  Jim Teresco, Williams College, Siena College

  CS 432, Spring 2005
  CSIS 330, Fall 2020
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  printf("This program (pid=%d) will magically become whatever program I specify\n", getpid());
  fflush(stdout);
  if (argc < 2) {
    fprintf(stderr, "Usage: %s program [arguments]\n", argv[0]);
    exit(1);
  }
  execvp(argv[1], &(argv[1]));
  printf("So this line never executes unless there's an error:\n");
  perror("execvp");
  return 1;
}
