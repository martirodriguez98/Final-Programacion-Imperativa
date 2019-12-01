#include <stdio.h>
#include <stdlib.h>
#include "library.h"
int main(int argc, char **argv)
{
	if(argc!=3)
	{
		printf("Error en la cantidad de argumentos. Pasar como parámetros el archivo de provincias y el de nacimientos\n");
		return 1;
	}
	provListADT prov=newProvList();
	FILE *f=fopen(argv[1],"r"); //abro el archivo de provincias que recibi como paramatro

	if(f==NULL)
	{
		printf("ERROR: No se pudo abrir el archivo\n");
		return 1;
	}

	cagarProvincias(f,prov); //cargo las estaciones al TAD
	fclose(f); //cuando termino de leer todas las provincias y agregarlas, cierro el archivo
}
