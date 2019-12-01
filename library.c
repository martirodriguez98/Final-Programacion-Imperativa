#define MAX_LINELENGTH 40
#include "provListADT.h"

void cargarProvincias(FILE * f, provListADT prov){
	char * buf=malloc(MAX_LINELENGTH); //creo un vector buffer para almacenar cada linea
	int cont=0;
	int numCampo;

	while(fgets(buf, BLOQUE2, f)){
		numCampo=0;
		cont++;

		if(cont==1)
			continue;	//me salteo el header que no quiero leer

		char * campo = strtok(buf, ",\n"); //empiezo a recorrer la linea del CSV
		int len;
		size_t id;
		char * name;
		while(campo){
			if(numCampo == 0){	//si leo el id lo guardo
				id=atoi(campo);
			}

			if(numCampo == 1){	//si leo el nombre lo guardo
				name=malloc(sizeof(campo));
				strcpy(name, campo);
			}

			campo=strtok(NULL, ",\n");	//avanzo de campo
			numCampo++;
		}
		addProvince(province, id, name);
		free(name);
	}
	free(buf);
}