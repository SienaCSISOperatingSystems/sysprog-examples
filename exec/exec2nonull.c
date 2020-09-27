/*
  Another little example of an exec system call
  This one forgets the NULL entry at the end of the
  argument vector and will cause an error or

  Jim Teresco, Williams College

  CS 432, Fall 2006

  Updated February 2010, Mount Holyoke College, CS 322
*/

#include <stdio.h>
#include <unistd.h>

int main() {
  char *argv[] = {"procinfo", "ls", "-l"};
  char *junk = "Some junk string!";
  int i = 27;

  printf("This program (pid=%d) will also magically become procinfo\n", getpid());
  execvp("./procinfo", argv);
  printf("So this line never executes unless there's an error:\n");
  perror("execvp");

  /* that probably failed -- let's see how it goes if we don't go too
     far off the end of our array */
  argv[4] = NULL;
  execvp("./procinfo", argv);
  printf("So this line never executes unless there's an error:\n");
  perror("execvp");
  return 1;
}
