COMPILER=gcc
OUTPUT_FILE=nacidos
FILES=nacidos.c library.c provListADT.c

all:
	$(COMPILER) -Wall -pedantic -std=c99 -fsanitize=address -o $(OUTPUT_FILE) $(FILES)
