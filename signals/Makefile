#
# Makefile for signal examples
#

PROGRAMS=sigalrm-example sigalrm-example2

all:	$(PROGRAMS)

sigalrm-example:	sigalrm-example.c
	gcc -o sigalrm-example sigalrm-example.c -lm

sigalrm-example2:	sigalrm-example2.c
	gcc -o sigalrm-example2 sigalrm-example2.c -lm

clean::
	/bin/rm -f $(PROGRAMS)
