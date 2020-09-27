/*
  Simple communication through an unnamed pipe

  Jim Teresco, Fall 2002, Operating Systems, Williams College

  Updated March 2005
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *text="Let's send this through a pipe";

int main() {
  int fd[2], size;
  char message[100];

  /* create the pipe */
  if (pipe(fd) == -1) {
    perror("pipe");
    exit(1);
  }

  if (fork() == 0) { /* child */
    /* the child will be writing -- close up the read end */
    close(fd[0]);
    write(fd[1], text, strlen(text)+1);  /* include NULL */
    /* all done - close up the write end */
    close(fd[1]);
  } else { /* parent */
    /* the parent will be reading -- close up the write end */
    close(fd[1]);
    size=read(fd[0], message, 100); /* read up to 100 bytes */
    /* all done - close up the read end */
    close(fd[0]);
    printf("Got %d bytes: <%s>\n", size, message);
  }
  return 0;
}
