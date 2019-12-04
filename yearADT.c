#include "yearADT.h"

typedef struct tYear{
	int year;
	long int male_births;
	long int female_births;
	long int no_sex_births;
	struct tYear * tail;
}tYear;

typedef struct yearListCDT{
	tYear * first;
	long int total_years;
}yearListCDT;

void addYear(yearADT y, int year){
	int flag=0;
	y->first=addRecYear(y->first,year,&flag);
	if(flag)
		y->total_years+=1;
}

static tYear * addRecYear(tYear * first, int year, int *flag){
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

size_t isEmptyYear(yearADT y){
	return y->first==NULL;
}

void freeYearList(yearADT y){
	freeRec(y->first);
	free(y);
}

static void freeRecYear(yearADT *first){
	if(first==NULL)
		return;
	freeRec(first->tail);
	free(first->year);
	free(first);
}

void printYear(yearADT y){
	tYear * aux=y->first;
	while(aux!=NULL){
		printf("%2d\ncant males:%d\ncant females:%d\ncant no sex:%d\n",aux->year,aux->male_births,aux->female_births,aux->no_sex_births);
		aux=aux->tail;
	}
}

  
