#
# Makefile for exec example

PROGRAMS=exec exec2 execwithargs execprocinfo procinfo execredir exec2nonull
CC=clang
CFLAGS=-Wall -g

all:	$(PROGRAMS)

# Look, no rules!  We use the builtin default rule that builds
# an executable from a .c file of the same name, using the C compile
# specified by CC (default is cc), and flags specified by CFLAGS

clean::
	/bin/rm -f $(PROGRAMS)
