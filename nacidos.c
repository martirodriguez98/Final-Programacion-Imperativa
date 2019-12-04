#include "library.h"
#include <stdio.h>
int main(int argc, char **argv)
{
	if(argc!=3)
	{
		printf("Error en la cantidad de argumentos. Pasar como parámetros el archivo de provincias y el de nacimientos\n");
		return 1;
	}
	dataADT prov=newProvList();
	FILE *f1=fopen(argv[1],"r"); //abro el archivo de provincias que recibi como paramatro
	FILE *f2=fopen(argv[2], "r"); //abro el archivo de nacimientos que recibi como parametro
	if(f1 == NULL || f2 == NULL){
		printf("ERROR al abrir los archivos.\n");
		return 1;
	}

	char separators[]=",";	//para poder cambiar el formato si se leyera de otra manera
	loadProvincies(f1,prov, separators); //cargo las estaciones al TAD
	fclose(f1); //cuando termino de leer todas las provincias y agregarlas, cierro el archivo
	loadData(f2, prov, separators);
	query1(prov);
	query2(prov);
	query3(prov);
	freeAll(prov);

	return 0;
}
