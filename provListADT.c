#include "provListADT.h"
#include <stdlib.h>
#include <string.h>
#define BUFFER 200
#define BLOQUE 20
#define MAX_LINELENGTH 40
typedef struct tProvince{
	char * name;
	int id;
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
	int year;
	long int male_births;
	long int female_births;
	long int unspecified;
	struct tYear * tail;
}tYear;	

provListADT newProvList(){
	return calloc(1, sizeof(provListCDT));
}

static char * copyName(char * name){
	char * s=NULL;
	int i;
		for (i = 0; name[i]!=0 && name[i]!='\r' && name[i]!='\n'; i++){
			if(i%BLOQUE == 0){
				s=realloc(s,i+BLOQUE);
			}
			s[i]=name[i];
		}
	s=realloc(s,i+1);  
	s[i]=0;
	return s;
}

static void copyStatic(char * st, char * source){
	int i=0;
	while(source[i] != 0){
		st[i] = source[i];
		i++;
	}
	st[i]=0;
}

static tProvince * addRec(tProvince * first ,int id, char * name);

void addProvince(provListADT p, int id, char name[]){
	p->first=addRec(p->first, id, name);
	p->total_provinces+=1; //siempre se agregara la provincia pues no se repiten
}

static tProvince * addRec(tProvince * first ,int id, char name[]){
	int c;
	if(first==NULL||(c=(strcmp(name,first->name))<0)){
		tProvince * prov=calloc(1,sizeof(tProvince));
		prov->name=copyName(name);
		prov->id=id;
		//printf("%zu %s\n", prov->id, prov->name);
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
		printf("%d %s %ld\n", aux->id, aux->name, aux->births);
		aux=aux->tail;
	}
	printf("\n--------------------\n");
	printf("Total: %ld\n", p->total_births);
	printf("\n--------------------\n");
	printYear(p);

}

static void listToArray(provListADT p, tProvince * arr){
	int i=0;
	arr[i++] = *(p->first);
	tProvince * aux = p->first;
	while(aux->tail!=NULL){
		arr[i++]=*(aux->tail);
		aux=aux->tail;
	}
}

void cargarProvincias(FILE * f, provListADT prov, char * separators){
	
	char * buf = malloc(BUFFER);
	int cont=0;
	int numCampo;
	while(fgets(buf, BUFFER, f)){
		numCampo=0;
		cont++;
		if(cont == 1)
			continue; //salteo el header
		char * campo = strtok(buf, separators);
		int id;
		while(campo){

			if(numCampo == 0){
				id=atoi(campo);
			}
			else if(numCampo == 1){
				addProvince(prov, id, campo);
			}
			campo = strtok(NULL, separators);
			numCampo++;
		}

	}
	free(buf);
}
				
static tProvince * getProvince(provListADT p, int id){
  
    tProvince * aux=p->first;

    while(aux != NULL){

        if(aux->id==id)
            return aux;
        
        aux=aux->tail;
    }

    return NULL;
}

static void addData(provListADT prov, int year, int id, char sex){
	tProvince * aux = getProvince(prov, id);
	prov->total_births+=1;
	aux->births+=1;
	addYear(prov, year, sex);
}

void cargarDatos(FILE * f, provListADT prov, char * separators){

	char * buf = malloc(BUFFER);
	int cont=0;
	int numCampo;
	//tProvince * provinceArr = malloc(sizeof(tProvince) * (prov->total_provinces));
	//listToArray(prov, provinceArr);
	while(fgets(buf, BUFFER, f)){
		int year;
		int id;
		char sex;
		numCampo=0;
		cont++;
		if(cont == 1)
			continue;	//salteo header
		char * campo=strtok(buf, separators);
		while(campo){
			if(numCampo == 0)
				year = atoi(campo);
			else if(numCampo == 1)
				id = atoi(campo);
			else if(numCampo == 3)
				sex = campo[0];
			campo = strtok(NULL, separators);
			numCampo++;

		}
		addData(prov, year, id, sex);
	}
	free(buf);

	//for(int i=0; i<prov->total_provinces;i++)
	//	printf("%zu,%s\n", provinceArr[i].id, provinceArr[i].name);
	
	//free(provinceArr);
}
static void addBySex(tYear * year, char sex){
	switch(sex-'0'){
		case 1: year->male_births+=1;break;
		case 2: year->female_births+=1;break;
		case 9: year->unspecified+=1;break;
		default:return;
	}
	return;
}
static tYear * addRecYear(tYear * first, int year, int *flag, char sex){
	int c;
	if(first==NULL || (c=year-first->year)<0){
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

void addYear(provListADT p, int year, char sex){
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
		printf("%d\ncant males:%ld\ncant females:%ld unsp:%ld\n",aux->year,aux->male_births,aux->female_births, aux->unspecified);
		aux=aux->tail;
	}
}

long int next(provListADT p, char name[]){
	long int aux=p->currentProv->births;
	copyStatic(name,p->currentProv->name);
	p->currentProv=p->currentProv->tail;
	return aux;
}

void toBegin(provListADT p){
	p->currentProv=p->first;
}

int hasNext(provListADT p){
	return p->currentProv!=NULL;
}

int nextYear(provListADT p, long int * male, long int * female){
	long int aux=p->currentYear->year;
	*male = p->currentYear->male_births;
	*female = p->currentYear->female_births;
	p->currentYear=p->currentYear->tail;
	return aux;
}

void toBeginYear(provListADT p){
	p->currentYear=p->firstYear;
}

int hasNextYear(provListADT p){
	return p->currentYear!=NULL;
}


int compareProvinces(const void * p1, const void * p2){
	int c2 = ((tProvince *)p2)->births;
	int c1 = ((tProvince *)p1)->births;

	int cmp = (c2 > c1) - (c2 < c1);
	if (cmp != 0)
		return cmp;
	else{
		return(strcmp(((tProvince *)p1)->name,((tProvince *)p2)->name));
	}
}
void copyPercentageData(provListADT p, FILE * f){
	fprintf(f, "Provincia;Porcentajes\n");
	tProvince * provinces = malloc((p->total_provinces) * sizeof(tProvince));
	listToArray(p, provinces);
	int i;
	for(i=0; i<p->total_provinces; i++)
		provinces[i].births = (provinces[i].births*100.0)/p->total_births;
	qsort(provinces, p->total_provinces, sizeof(tProvince), &compareProvinces);
	for(i=0 ; i<p->total_provinces ;i++){
		fprintf(f, "%s;%%%ld\n",provinces[i].name,provinces[i].births);
	}
	free(provinces);
}
 
hola


