/*
  A pipe between two child processes.

  The first program to run is specified in argv[1], followed by 0 or
  more of its command-line parameters.  Then the keyword TO is
  required.  The next command-line parameter is the second program to
  run, followed by 0 or more of its command-line parameters.

  Jim Teresco, Fall 2022, Operating Systems, Siena College
*/  
  
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void usage(char *progname) {
  fprintf(stderr, "Usage: %s command1 [args] TO command2 [args]\n", progname);
}

int main(int argc, char *argv[]) {

  // at least 4 parameters are needed
  if (argc < 4) {
    usage(argv[0]);
    exit(1);
  }

  int to_pos = -1;
  // some parameter starting at argv[2] must be the TO keyword
  for (int i=2; i<argc; i++) {
    if (strcmp(argv[i],"TO") == 0) {
      to_pos = i;
      break;
    }
  }

  // did we find "TO"?
  if (to_pos == -1) {
    usage(argv[0]);
    exit(1);
  }

  // is there at least one more command-line parameter after to_pos?
  if (to_pos == argc-1) {
    usage(argv[0]);
    exit(1);
  }

  // set up the parameters for the child processes
  char **p1argv, **p2argv;
  int p1argc, p2argc;
  p1argc = to_pos - 1;
  p1argv = (char **)malloc((p1argc+1)*sizeof(char *));
  for (int i = 0; i < p1argc; i++) {
    p1argv[i] = argv[i+1];
  }

  p2argc = argc - to_pos - 1;
  p2argv = (char **)malloc((p1argc+1)*sizeof(char *));
  for (int i = 0; i < p2argc; i++) {
    p2argv[i] = argv[i+to_pos+1];
  }

  printf("First process argc = %d\n", p1argc);
  for (int i = 0; i < p1argc; i++) {
    printf("argv[%d] = %s\n", i, p1argv[i]);
  }
  printf("Second process argc = %d\n", p2argc);
  for (int i = 0; i < p2argc; i++) {
    printf("argv[%d] = %s\n", i, p2argv[i]);
  }

  // we will create two child processes
  int p1pid, p2pid;
  // a pair of file descriptors for the pipe
  int pipefd[2];
  int retval;

  // create the pipe
  retval = pipe(pipefd);
  if (retval == -1) {
    perror("pipe");
    exit(1);
  }
  
  // create the process for the second program in the pipeline first
  p2pid = fork();
  if (p2pid == -1) {
    perror("fork");
    exit(1);
  }
  if (p2pid) {
    // parent, need to create the process for the first program
    // in the pipeline
    p1pid = fork();
    if (p1pid == -1) {
      perror("fork");
      exit(1);
    }
    if (p1pid) {

      // parent closes both ends of the pipe
      close(pipefd[0]);
      close(pipefd[1]);
      
      // still parent, here we wait for both children
      waitpid(p1pid, NULL, 0);
      waitpid(p2pid, NULL, 0);
    }
    else {
      // child to be used for the first process in the pipeline

      // this process needs to attach is stdout to the write end of the
      // pipe and close the read end
      dup2(pipefd[1], 1);
      close(pipefd[0]);

      // do it
      execvp(p1argv[0], p1argv);
    }
  }
  else {
    // child to be used for the second process in the pipeline

    // this process needs to attach is stdin to the read end of the
    // pipe and close the write end
    dup2(pipefd[0], 0);
    close(pipefd[1]);
    
    // do it
    execvp(p2argv[0], p2argv);
  }
  
  return 0;
}
