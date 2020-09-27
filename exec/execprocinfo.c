/*
  Little example of an exec system call

  Jim Teresco, Williams College

  CS 432, Spring 2005

  Updated, Spring 2008, Mount Holyoke College, CS 322
*/

#include <stdio.h>
#include <unistd.h>

int main() {

  printf("This program (pid=%d) will magically become procinfo\n", getpid());
  execlp("./procinfo", "heythisisnotprocinfo", "17", "-l", "Hey!", NULL);
  printf("So this line never executes unless there's an error:\n");
  perror("execlp");
  return 1;
}
