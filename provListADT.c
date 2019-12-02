#include "provListADT.h"
#include <stdlib.h>
#include <string.h>

typedef struct tProvince{
	char * name;
	int id;
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

static void copyName(tProvince * prov, char * name){
	int i=0;
	prov->name=NULL;
	while(name[i]!=0){
		if(i%BLOQUE==0){
			prov->name=realloc(1,sizeof(i+BLOQUE));
		}
		prov->name[i]=name[i];
		i++;
	}
	prov->name=realloc(1,sizeof(i));
}

void addProvince(provListADT p, size_t id, char * name){
	p->first=addRec(p->first, id, name);
	p->total_provinces+=1; //siempre se agregara la provincia pues no se repiten
}

tProvince * addRec(tProvince * first ,size_t id, char * name){
	int c;
	if(first==NULL||(c=(strcmp(name,first->name))<0)){
		tProvince * prov=calloc(1,sizeof(tProvince));
		copyName(prov, name);
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
		printf("%2d %s\n",aux->id, aux->name);
		aux=aux->tail;
	}
}
