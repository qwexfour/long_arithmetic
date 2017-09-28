
CC=gcc
CFLAGS= -std=c11 -Wall
DBGINFO= 


all: a.out

test: iotest.out

a.out: main.o longalib.o
	$(CC) $(CFLAGS) main.o longalib.o -lm -o a.out $(DBGINFO)

iotest.out: iotest.o longalib.o
	$(CC) $(CFLAGS)  iotest.o longalib.o -lm -o iotest.out $(DBGINFO)

main.o: longalib.h main.c
	$(CC) $(CFLAGS) -c main.c -lm -o main.o $(DBGINFO)

longalib.o: longalib.h longalib.c
	$(CC) $(CFLAGS) -c longalib.c -lm -o longalib.o $(DBGINFO)

iotest.o: longalib.h iotest.c
	$(CC) $(CFLAGS) -c iotest.c -o iotest.o $(DBGINFO)



clear:
	rm *.o *.out
	
	
