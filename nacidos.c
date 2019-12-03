#include "library.h"
#include <stdio.h>
int main(int argc, char **argv)
{
	if(argc!=3)
	{
		printf("Error en la cantidad de argumentos. Pasar como parámetros el archivo de provincias y el de nacimientos\n");
		return 1;
	}
	provListADT prov=newProvList();
	FILE *f1=fopen(argv[1],"r"); //abro el archivo de provincias que recibi como paramatro
	FILE *f2=fopen(argv[2], "r"); //abro el archivo de nacimientos que recibi como parametro
	if(f1 == NULL || f2 == NULL){
		printf("ERROR al abrir los archivos.\n");
		return 1;
	}
	char format[]="%zu,%[^\n]";
	cargarProvincias(f1,prov, format); //cargo las estaciones al TAD
	fclose(f1); //cuando termino de leer todas las provincias y agregarlas, cierro el archivo
	char format2[]="%zu,%zu,%*zu,%zu,%*[^\n]";
	
	cargarDatos(f2, prov, format2);
		


	print(prov);
	query1(prov);

	freeAll(prov);

	return 0;
}
