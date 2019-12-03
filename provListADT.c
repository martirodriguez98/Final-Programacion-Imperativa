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
	struct tProvince * currentProv;
	long int total_births;
	long int total_provinces;
	long int total_years;
	struct tYear * firstYear;
	struct tYear * currentYear;
}provListCDT;

typedef struct tYear{
	size_t year;
	long int male_births;
	long int female_births;
	struct tYear * tail;
}tYear;

provListADT newProvList(){
	return calloc(1, sizeof(provListCDT));
}

static char * copyName(char * name){
	int i=0;
	char * aux=NULL;
	while(name[i]!=0){
		if(i%BLOQUE==0){
			aux=realloc(aux,i+BLOQUE);
		}
		aux[i]=name[i];
		i++;
	}
	aux[i++]=0;
	aux=realloc(aux,i);

	return aux;
}

static void copyStatic(char * st, char * source){
	int i=0;
	while(source[i] != 0){
		st[i] = source[i];
		i++;
	}
	st[i]=0;
}

static tProvince * addRec(tProvince * first ,size_t id, char * name);

void addProvince(provListADT p, size_t id, char name[]){
	p->first=addRec(p->first, id, name);
	p->total_provinces+=1; //siempre se agregara la provincia pues no se repiten
}

tProvince * addRec(tProvince * first ,size_t id, char name[]){
	int c;
	if(first==NULL||(c=(strcmp(name,first->name))<0)){
		tProvince * prov=calloc(1,sizeof(tProvince));
		prov->name=malloc(strlen(name)+1);
		strcpy(prov->name, name);
		prov->id=id;
		printf("%s %zu\n", prov->name, prov->id);
		prov->tail=first;
		return prov;
	}
	first->tail=addRec(first->tail,id,name);
	return first;
}

size_t isEmpty(provListADT p){
	return p->first==NULL;
}


void print(provListADT p){
	tProvince * aux=p->first;
	while(aux!=NULL){
		printf("%2zu, %s, %ld\n",aux->id, aux->name, aux->births);
		aux=aux->tail;
	}
	printf("\n--------------------\n");
	printYear(p);
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

void cargarProvincias(FILE * f, provListADT prov, char * format){
	
	size_t id;
	char name[MAX_LINELENGTH];

	while(fgetc(f) != '\n'); //salteo el header
	while(fscanf(f, format, &id, name) == 2){
		addProvince(prov, id, name);
	}
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
	addYear(prov, year, sex);

}

void cargarDatos(FILE * f, provListADT prov, char * format){
	size_t year;
	size_t id;
	size_t sex;
	//tProvince * provinceArr = malloc(sizeof(tProvince) * (prov->total_provinces));
	//listToArray(prov, provinceArr);
	
	while(fgetc(f) != '\n'); //salteo el header
	while(fscanf(f, format, &year, &id, &sex)){
		addData(prov, year, id, sex);
	}

	//for(int i=0; i<prov->total_provinces;i++)
	//	printf("%zu,%s\n", provinceArr[i].id, provinceArr[i].name);
	
	//free(provinceArr);
}
static void addBySex(tYear * year, size_t sex){
	switch(sex){
		case 1: year->male_births+=1;break;
		case 2: year->female_births+=1;break;
		default:return;
	}
	return;
}
static tYear * addRecYear(tYear * first, size_t year, int *flag, size_t sex){
	int c;
	if(first==NULL || (c=year-first->year)<0)
	{
		tYear *aux=calloc(1,sizeof(tYear));
		aux->year=year;
		aux->tail=first;
		addBySex(aux, sex);
		(*flag)=1;
		return aux;
	}
	else if(c==0){
		addBySex(first, sex);
		return first;
	}
	first->tail=addRecYear(first->tail,year,flag,sex);
	return first;
}

void addYear(provListADT p, size_t year, size_t sex){
	int flag=0;
	p->firstYear=addRecYear(p->firstYear,year,&flag,sex);
	if(flag)
		p->total_years+=1;
}

size_t isEmptyYear(provListADT p){
	return p->firstYear==NULL;
}

static void freeRec(tProvince * first){
	if(first==NULL)
		return;
	freeRec(first->tail);
	free(first->name);
	free(first);
	
}

static void freeProvList(provListADT p){
	freeRec(p->first);
}

static void freeRecYear(tYear *first){
	if(first==NULL)
		return;
	freeRecYear(first->tail);
	free(first);
}

static void freeYearList(provListADT p){
	freeRecYear(p->firstYear);
}

void freeAll(provListADT p){
	freeYearList(p);
	freeProvList(p);
	free(p);
}

void printYear(provListADT p){
	tYear * aux=p->firstYear;
	while(aux!=NULL){
		printf("%2zu\ncant males:%ld\ncant females:%ld\n",aux->year,aux->male_births,aux->female_births);
		aux=aux->tail;
	}
}

void toBegin(provListADT p){
	p->currentProv=p->first;
}

int hasNext(provListADT p){
	return p->currentProv!=NULL;
}

long int next(provListADT p, char name[]){
	long int aux=p->currentProv->births;
	copyStatic(name,p->currentProv->name);
	p->currentProv=p->currentProv->tail;
	return aux;
}

	


