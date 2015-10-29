CC=gcc
FLAGS_DEBUG=-Wall -std=c11 -ggdb
FLAGS_PROD=-Wall -pg -std=c11 


all: lager

lager:	lager.o interface.o input.o output.o db.o pallet.o good.o shelf.o list.o tree.o

%.o: %.c
		$(CC) $(FLAGS_DEBUG) $^ -c -o $@




clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f lager
	rm -f tree
	rm -f interface
	rm -f shelf
	rm -f db
	rm -f good
	rm -f output
	rm -f input
	rm -f *~ 
