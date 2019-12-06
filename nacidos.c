#include "library.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
int main(int argc, char **argv)
{
	if(argc!=3)
	{
		printf("Error en la cantidad de argumentos. Pasar como parámetros el archivo de provincias y el de nacimientos\n");
		return 1;
	}
	dataADT prov=newProvList();
	if(prov == NULL){
		fprintf(stderr, "ERROR: %s\n", strerror(ENOMEM));
		exit(ENOMEM);
	}		

	FILE *f1=fopen(argv[1],"r"); //abro el archivo de provincias que recibi como paramatro
	FILE *f2=fopen(argv[2], "r"); //abro el archivo de nacimientos que recibi como parametro
	if(f1 == NULL || f2 == NULL){
		fprintf(stderr, "ERROR: %s\n", strerror(ENOENT));
		exit(ENOENT);
	}

	char separators[]=",";	//para poder cambiar el formato si se leyera de otra manera
	if(loadProvinces(f1,prov, separators) == ERROR){ //cargo las estaciones al TAD
		fprintf(stderr, "ERROR: %s\n", strerror(ENOMEM));
		freeAll(prov);
		exit(ENOMEM);
	}
	fclose(f1); //cuando termino de leer todas las provincias y agregarlas, cierro el archivo
	
	if(loadData(f2, prov, separators) == ERROR){
		fprintf(stderr, "ERROR: %s\n", strerror(ENOMEM));
		freeAll(prov);
		exit(ENOMEM);
	}
	query1(prov);
	query2(prov);
	if(query3(prov)==ERROR){
		fprintf(stderr, "ERROR: %s\n", strerror(ENOMEM));
		freeAll(prov);
		exit(ENOMEM);
	}
	freeAll(prov);
	return 0;
}
