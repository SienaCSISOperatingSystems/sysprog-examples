/*
  Little example to be used by an exec system call

  Jim Teresco, Williams College

  CS 432, Spring 2005, Updated Fall 2006
*/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int i;

  printf("This is the procinfo program\n");
  printf("pid=%d\n", getpid());
  printf("argc=%d\n", argc);
  for (i=0; i<argc; i++) {
    printf("argv[%d] = %p <%s>\n", i, argv[i], argv[i]);
  }
  /* let's look one beyond the end of the array, also,
   but only at the pointer (not what it points to) */
  printf("argv[%d] = %p\n", argc, argv[argc]);

  return 0;
}
