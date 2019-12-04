COMPILER=gcc
OUTPUT_FILE=nacidos

all: compile
	rm -r *.o *.h.gch

compile: sources.o library.o
	$(COMPILER) -Wall -pedantic -std=c99 -fsanitize=address -o $(OUTPUT_FILE) nacidos.c sources.o library.o

sources.o: provListADT.c provListADT.h
	$(COMPILER) -c provListADT.c provListADT.h

library.o: library.c library.h
	$(COMPILER) -c library.c library.h