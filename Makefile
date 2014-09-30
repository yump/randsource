CC=gcc 
CFLAGS=-Wall --std=c11 -O3 -march=native

all: randsource

debug: CFLAGS += -g
debug: randsource
randsource: randsource.o
randsource.o: randsource.c

clean:
	rm -f randsource randsource.o

