/*
  Simple communication through a named pipe (fifo)

  Jim Teresco, Fall 2002, Operating Systems, Williams College
  Added more output, October 2006
*/  
  
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

void read_from_pipe() {
  int fd, size;
  char message[100];

  printf("Opening pipe for reading\n");
  fd=open("testpipe", O_RDONLY);
  if (fd == -1) {
    perror("open");
    exit(1);
  }
  size=read(fd, message, 100); /* read up to 100 bytes */
  close(fd);
  printf("Got %d bytes: <%s>\n", size, message);
}

void write_to_pipe() {
  int fd;
  char message[100];

  printf("Opening pipe for writing\n");
  fd=open("testpipe", O_WRONLY);
  if (fd == -1) {
    perror("open");
    exit(1);
  }
  printf("Enter your message (limit 100 chars):\n");
  fgets(message, 100, stdin);
  write(fd, message, strlen(message)+1);  /* include NULL */
  close(fd);
}

void usage(char *progname) {
  fprintf(stderr, "Usage: %s read|write\n", progname);
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    usage(argv[0]);
    exit(1);
  }

  if (strcmp(argv[1], "write") == 0) 
    write_to_pipe();
  else if (strcmp(argv[1], "read") == 0) 
    read_from_pipe();
  else {
    usage(argv[0]);
    exit(1);
  }

  return 0;
}
