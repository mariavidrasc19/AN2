# Makefile pentru tema
CC=g++
CFLAGS= -std=c++11 -Wall -Wextra -Wpedantic
OBJFLAG = -c

build:
	$(CC) $(CFLAGS) $(OBJFLAG) bani.cpp -o prob1.o
	$(CC) $(CFLAGS) $(OBJFLAG) gard.cpp -o prob2.o
	$(CC) $(CFLAGS) $(OBJFLAG) bomboane.cpp -o prob3.o
	$(CC) $(CFLAGS) $(OBJFLAG) sala.cpp -o prob4.o
	$(CC) prob1.o -o bani
	$(CC) prob2.o -o gard
	$(CC) prob3.o -o bomboane
	$(CC) prob4.o -o sala

run-p1:
	./bani

run-p2:
	./gard

run-p3:
	./bomboane

run-p4:
	./sala

clean:
	rm -rf prob1.o
	rm -rf prob2.o
	rm -rf prob3.o
	rm -rf prob4.o
	rm -rf bani
	rm -rf gard
	rm -rf bomboane
	rm -rf sala
