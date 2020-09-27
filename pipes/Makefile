#
# Makefile for pipe examples
#

PROGRAMS=pipe1 pipe2 pipeprocs

all:	$(PROGRAMS)

pipe1:	pipe1.c
	gcc -o pipe1 pipe1.c

pipe2:	pipe2.c
	gcc -o pipe2 pipe2.c

pipeprocs:	pipeprocs.c
	gcc -o pipeprocs pipeprocs.c

clean::
	/bin/rm -f $(PROGRAMS)
