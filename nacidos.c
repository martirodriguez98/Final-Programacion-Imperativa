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
	if(prov == NULL){
		printf(ERROR_MESSAGE);
		return ERROR;
	}		

	FILE *f1=fopen(argv[1],"r"); //abro el archivo de provincias que recibi como paramatro
	FILE *f2=fopen(argv[2], "r"); //abro el archivo de nacimientos que recibi como parametro
	if(f1 == NULL || f2 == NULL){
		printf("ERROR al abrir los archivos.\n");
		return 1;
	}

	char separators[]=",";	//para poder cambiar el formato si se leyera de otra manera
	if(loadProvinces(f1,prov, separators) == ERROR){ //cargo las estaciones al TAD
		printf(ERROR_MESSAGE);
		freeAll(prov);
		return ERROR;
	}
	fclose(f1); //cuando termino de leer todas las provincias y agregarlas, cierro el archivo
	
	if(loadData(f2, prov, separators) == ERROR){
		printf(ERROR_MESSAGE);
		freeAll(prov);
		return ERROR;
	}
	query1(prov);
	query2(prov);
	if(query3(prov)==ERROR){
		printf(ERROR_MESSAGE);
		freeAll(prov);
		return ERROR;
	}
	freeAll(prov);
	return 0;
}
