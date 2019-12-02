#define MAX_LINELENGTH 40
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "library.h"
#include "provListADT.h"

void cargarProvincias(FILE * f, provListADT prov){
	char format[]="%zu,%s\n"
	size_t id;
	char * name = malloc(MAX_LENGTH);

	while(fgetc(prov) != '\n'); //salteo el header
	while(fscanf(prov, format, &id, name) == 2){
		addProvince(prov, id, name);
	}

	free(name);
}
