#include "yearADT.h"

typedef struct tYear{
	size_t year;
	long int male_births;
	long int female_births;
	long int no_sex_births;
	struct tYear * tail;
}tYear;

typedef struct yearListCDT{
	tYear * first;
	long int total_years;
}yearListCDT;

void addYear(yearADT y, size_t year){
	int flag=0;
	y->first=addRec(y->first,year,&flag);
	if(flag)
		y->total_years+=1;
}

static tYear * addRec(tYear * first, size_t year, int *flag){
	int c;
	if(first==NULL || (c=year-first->year)<0)
	{
		tYear *aux=calloc(1,sizeof(tYear));
		aux->year=year;
		aux->tail=first;
		(*flag)=1;
		return aux;
	}
	else if(c==0)
		return first;
	first->tail=addRec(first->tail,year,flag);
}

size_t isEmpty(yearADT y){
	return y->first==NULL;
}

void freeYearList(yearADT y){
	freeRec(y->first);
	free(y);
}

static void freeRec(yearADT *first){
	if(first==NULL)
		return;
	freeRec(first->tail);
	free(first->year);
	free(first);
}

void print(yearADT y){
	tYear * aux=y->first;
	while(aux!=NULL){
		printf("%2d\ncant males:%d\ncant females:%d\ncant no sex:%d\n",aux->year,aux->male_births,aux->female_births,aux->no_sex_births);
		aux=aux->tail;
	}
}

  
