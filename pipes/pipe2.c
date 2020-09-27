/*
  Simple communication through a named pipe (fifo)

  Jim Teresco, Fall 2002, Operating Systems, Williams College
*/  
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

char *text="Let's send this through a named pipe";

int main() {
  int fd, size;
  char message[100];

  if (fork() == 0) { /* child */
    fd=open("testpipe", O_WRONLY);
    if (fd == -1) {
      perror("open");
      exit(1);
    }
    write(fd, text, strlen(text)+1);  /* include NULL */
    close(fd);
  } else { /* parent */
    fd=open("testpipe", O_RDONLY);
    if (fd == -1) {
      perror("open");
      exit(1);
    }
    size=read(fd, message, 100); /* read up to 100 bytes */
    close(fd);
    printf("Got %d bytes: <%s>\n", size, message);
  }
  return 0;
}
