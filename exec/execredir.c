/*
  Little example of an exec system call and output redirection

  Jim Teresco, Williams College

  CS 432, Spring 2005
  CSIS 330, Fall 2020, Siena College
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int fd;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    exit(1);
  }

  printf("We will create and open a new file %s for writing\n", argv[1]);
  fd = open(argv[1], O_CREAT|O_WRONLY, 0644);
  if (fd == -1) {
    perror("open");
    exit(1);
  }

  printf("After this line, all stdout will be redirected to the file\n");
  if (dup2(fd,1) == -1) {
    perror("dup2");
    exit(1);
  }

  printf("This should be in the output file\n");
  printf("Now we will exec to do an ls -l\n");
  fflush(stdout);
  execlp("ls", "ls", "-l", NULL);
  printf("So this line never executes unless there's an error:\n");
  perror("execlp");
  return 1;
}
