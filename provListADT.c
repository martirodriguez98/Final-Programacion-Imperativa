#include "provListADT.h"
#include <stdlib.h>
#include <string.h>
#define BLOQUE 20
#define MAX_LINELENGTH 40
typedef struct tProvince{
	char * name;
	size_t id;
	long int births;
	struct tProvince * tail;
}tProvince;

typedef struct provListCDT{
	struct tProvince * first;
	long int total_births;
	long int total_provinces;
}provListCDT;


provListADT newProvList(){
	return calloc(1, sizeof(provListCDT));
}

static tProvince * addRec(tProvince * first ,size_t id, char * name);

void addProvince(provListADT p, size_t id, char * name){
	p->first=addRec(p->first, id, name);
	p->total_provinces+=1; //siempre se agregara la provincia pues no se repiten
}

tProvince * addRec(tProvince * first ,size_t id, char * name){
	int c;
	if(first==NULL||(c=(strcmp(name,first->name))<0)){
		tProvince * prov=calloc(1,sizeof(tProvince));
		prov->name=malloc(strlen(name)+1);
		strcpy(prov->name, name);
		prov->id=id;
		prov->tail=first;
		return prov;
	}
	first->tail=addRec(first->tail,id,name);
	return first;
}

size_t isEmpty(provListADT p){
	return p->first==NULL;
}

static void freeRec(tProvince * first);

void freeProvList(provListADT p){
	freeRec(p->first);
	free(p);
}

static void freeRec(tProvince * first){
	if(first==NULL)
		return;
	freeRec(first->tail);
	free(first->name);
	free(first);
	
}


void print(provListADT p){
	tProvince * aux=p->first;
	while(aux!=NULL){
		printf("%2zu, %ld, %s\n",aux->id, aux->births, aux->name);
		aux=aux->tail;
	}
}

static void listToArray(provListADT p, tProvince * arr){
	tProvince * aux=p->first;
	int i=0;
	while(aux!=NULL)
	{
		arr[i]=*aux;
		aux=aux->tail;
		i++;
	}
}

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

static tProvince * getProvince(provListADT p, size_t id){
  
    tProvince * aux=p->first;

    while(aux != NULL){

        if(aux->id==id)
            return aux;
        
        aux=aux->tail;
    }

    return NULL;
}

static void addData(provListADT prov, int year, size_t id, size_t sex){
	tProvince * aux = getProvince(prov, id);
	prov->total_births+=1;
	aux->births+=1;
}

void cargarDatos(FILE * f, provListADT prov){
	char format[]="%d,%d,%*d,%d,%*[^\n]";
	int year;
	size_t id;
	size_t sex;
	//tProvince * provinceArr = malloc(sizeof(tProvince) * (prov->total_provinces));
	//listToArray(prov, provinceArr);
	
	while(fgetc(f) != '\n'); //salteo el header
	while(fscanf(f, format, &year, &id, &sex)){
		addData(prov, year, id, sex);
		//printf("%d %zu %zu\n", year, id, sex);
	}

	//for(int i=0; i<prov->total_provinces;i++)
	//	printf("%zu,%s\n", provinceArr[i].id, provinceArr[i].name);
	
	//free(provinceArr);
}






