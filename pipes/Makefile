#
# Makefile for pipe examples
#
CC=clang
PROGRAMS=pipe1 pipe2 pipeprocs pipefork

all:	$(PROGRAMS)

pipe1:	pipe1.c
	$(CC) -o pipe1 pipe1.c

pipe2:	pipe2.c
	$(CC) -o pipe2 pipe2.c

pipeprocs:	pipeprocs.c
	$(CC) -o pipeprocs pipeprocs.c

pipefork:	pipefork.c
	$(CC) -o pipefork pipefork.c

clean::
	/bin/rm -f $(PROGRAMS)
