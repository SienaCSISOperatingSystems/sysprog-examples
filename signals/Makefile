#
# Makefile for signal examples
#
CC=clang
PROGRAMS=sigalrm-example sigalrm-example2

all:	$(PROGRAMS)

sigalrm-example:	sigalrm-example.c
	$(CC) -o sigalrm-example sigalrm-example.c -lm

sigalrm-example2:	sigalrm-example2.c
	$(CC) -o sigalrm-example2 sigalrm-example2.c -lm

clean::
	/bin/rm -f $(PROGRAMS)
