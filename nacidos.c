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
	}

	cargarProvincias(f1,prov); //cargo las estaciones al TAD
	fclose(f1); //cuando termino de leer todas las provincias y agregarlas, cierro el archivo
	
	cargarDatos(f2, prov);
		


	print(prov);

	freeProvList(prov);

	return 0;
}
