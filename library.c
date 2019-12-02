#define MAX_LINELENGTH 40
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "library.h"
#include "provListADT.h"

void cargarProvincias(FILE * f, provListADT prov){
	char format[]="%zu,%[^\n]";
	size_t id;
	char * name = malloc(MAX_LINELENGTH);

	while(fgetc(f) != '\n'); //salteo el header
	while(fscanf(f, format, &id, name) == 2){
		addProvince(prov, id, name);
	}

	free(name);
}

void cargarDatos(FILE * f, provListADT prov){
	char format[]="%d,%d,%*d,%d,%*s";
	
}
