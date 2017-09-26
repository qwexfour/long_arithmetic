
CC=gcc
CFLAGS= -std=c11 -Wall


all: iotest.out

iotest.out: iotest.o longalib.o
	$(CC) $(CFLAGS)  iotest.o longalib.o -o iotest.out

longalib.o: longalib.h longalib.c
	$(CC) $(CFLAGS) -c longalib.c -o longalib.o

iotest.o: longalib.h iotest.c
	$(CC) $(CFLAGS) -c iotest.c -o iotest.o



clear:
	rm *.o *.out
	
	
