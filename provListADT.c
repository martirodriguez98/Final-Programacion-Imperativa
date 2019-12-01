#include "provListADT.h"

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

void addProvince(provListADT p, size_t id, char * name){
	p->first=addRec(p->first, id, name);
	p->total_provinces+=1; //siempre se agregara la provincia pues no se repiten
}

tProvince * addRec(tProvince * first ,size_t id, char * name){
	int c;
	if(first==NULL||(c=(strcmp(name,first->name))<0)){
		tProvince * prov=calloc(1,sizeof(tProvince));
		prov->name=malloc(sizeof(strlen(name))); //PUEDE FALLAR
		strcpy(prov->name,name);
		prov->id=id;
		prov->tail=first;
		return prov;
	}
	if(c==0)
		return first;

	first->tail=addRec(first->tail,id,name);
	return first;
}

size_t isEmpty(provListADT p){
	return p->first==NULL;
}



/*
void freeProvList(provListADT p){

}
*/

void print(provListADT p){
	tProvince * aux=p->first;
	while(aux!=NULL){
		printf("%d\t%s\n",aux->id,aux->name);
		aux=aux->tail;
	}
}
