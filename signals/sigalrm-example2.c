/*
  Example of SIGALRM usage with SIGTERM, SIGINT, SIGTSTP trapping

  Jim Teresco, Fall 2002, Computer Science 432, Williams College

  Updated to new setitimer, March 2005
  Added pid printout, October 2006
*/
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>

/* we make some variables global so they can be seen easily from
   the signal handler and the main program */
time_t start_time;
int i,j,k;
double ans=0.0;

/* Our signal handler.  We will tell the system to call this
   function whenever it gets a SIGALRM */
void sigFunc(int sig) {

  printf("sigFunc got signal: %d\n", sig);
  switch (sig) {
  case SIGALRM:
    printf("Alarm!  Alarm!  %d got SIGALRM at time %ld\n", getpid(),
	   time(NULL)-start_time);
    printf("i=%d, j=%d, k=%d, ans=%f\n",i,j,k,ans);
    break;
  case SIGINT:
    printf("Hey, I'm working here!  Go SIGINT someone else!\n");
    break;
  case SIGTERM:
    printf("Ha!  I laugh at your little SIGTERM\n");
    printf("And now I'm going to send myself a SIGINT!\n");
    kill(getpid(), SIGINT);
    break;
  default:
    printf("This shouldn't happen...\n");
    break;
  }
}

int main() {
  struct itimerval alarmset;

  /* remember starting time - this returns the number of seconds
     since the Unix epoch at 1970/01/01 00:00:00 */
  start_time=time(NULL);
  printf("This program will compute for a long time, but\n");
  printf("will handle SIGALRM events asynchronously to\n");
  printf("report on its progress every 5 seconds\n");
  /* set up our signal handler to catch SIGALRM */
  signal(SIGALRM, sigFunc);

  /* Also trap SIGINT */
  signal(SIGINT, sigFunc);

  /* And trap SIGTERM - the default kill signal */
  signal(SIGTERM, sigFunc);

  /* We'll ignore SIGTSTP altogether */
  signal(SIGTSTP, SIG_IGN);

  /* We'll ignore SIGHUP too */
  signal(SIGHUP, SIG_IGN);

  /* start the timer - we want to wake up every 5 seconds */
  /*was: alarm(5);*/
  alarmset.it_interval.tv_sec = 5;
  alarmset.it_interval.tv_usec = 0;
  alarmset.it_value.tv_sec = 5;
  alarmset.it_value.tv_usec = 0;
  if (setitimer(ITIMER_REAL, &alarmset, NULL)) {
    perror("setitimer");
    exit(1);
  }

  /* compute stuff for a long time */
  for (i=0;i<10000;i++)
    for (j=0;j<10000;j++)
      for(k=0;k<10000;k++)
	ans=ans+sqrt(i)+sqrt(j)-sqrt(k);

  /* for the very patient... */
  printf("Answer is: %f\n", ans);
  return 0;
}

