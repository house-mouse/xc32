SHELL := /bin/bash

OBJS = lex.yy.o grammar.tab.o main.o resource.o
READER_OBJS = reader.o resource.o

CC=gcc
INCLUDE= -I. -I../c30 -I../xc32
CFLAGS= -g $(INCLUDE) $(PIC32) $(EXTRA_CFLAGS)

rg:	$(OBJS) reader
	$(CC) -o $@ $(OBJS) $(CFLAGS)

reader: $(READER_OBJS)
	$(CC) -o $@ $(READER_OBJS) $(CFLAGS)

grammar.tab.c: grammar.y grammar.h
	bison -v -t -d `basename $<`

lex.yy.c: grammar.l grammar.tab.c
	flex -f `basename $<`

clean: 
	rm lex.yy.o grammar.tab.o main.o resource.o reader.o	
