CC=gcc
FLAGS_DEBUG=-Wall -std=c11 -ggdb
FLAGS_PROD=-Wall -std=c11


all: lager

lager:	lager.o	interface.o db.o pallet.o good.o shelf.o list.o tree.o

%.o: %.c
					$(CC) $(FLAGS_DEBUG) $^ -c -o $@



clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f main
	rm -f interface
	rm -f shelf
	rm -f db
	rm -f good
