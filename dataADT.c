#include "dataADT.h"
#include <stdlib.h>
#include <string.h>
#define BUFFER 200
#define BLOCK 20
#define MAX_LINELENGTH 40

typedef struct tProvince{
	char * name;
	int id;
	long int births;
	struct tProvince * tail;
}tProvince;

typedef struct tYear{
	int year;
	long int male_births;
	long int female_births;
	struct tYear * tail;
}tYear;	

typedef struct dataCDT{
	struct tProvince * firstProv;
	struct tProvince * currentProv;
	long int total_births;
	long int total_provinces;
	long int total_years;
	struct tYear * firstYear;
	struct tYear * currentYear;
}dataCDT;

static char * copyName(char * name);//copia el string nombre leido del csv a un vector y lo devuelve
static void copyStatic(char * st, char * source);//copia un string a un vector estatico (fijo)
static tProvince * addRec(tProvince * firstProv ,int id, char name[], int * flag);
static void listToArray(dataADT p, tProvince * arr);//pasa la lista de provincias a un array
static tProvince * getProvince(dataADT p, int id);//busca la provincia en la lista y la devuelve
static int addData(dataADT prov, int year, int id, char sex);//añade datos a la provincia buscandola por id
static void freeRec(tProvince * firstProv);
static void freeProvList(dataADT p);
static void freeRecYear(tYear *firstYear);
static void freeYearList(dataADT p);
static void addBySex(tYear * year, char sex);//añade nacimiento al año dependiendo del sexo
static tYear * addRecYear(tYear * firstYear, int year, int *flag, char sex, int * errorcheck);

dataADT newProvList(){
	return calloc(1, sizeof(dataCDT));
}

static char * copyName(char * name){
	char * s=NULL;
	int i;
		for (i = 0; name[i]!=0 && name[i]!='\r' && name[i]!='\n'; i++){//se considera omitir el caracter /r pues estaba presente en los
			if(i%BLOCK == 0){											//csv y generaba problemas en la impresion del string
				char * aux = s;
				aux=realloc(s,i+BLOCK);
				if(aux == NULL){
					free(s);
					return NULL;
				}
				s=aux;
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

static void listToArray(dataADT p, tProvince * arr){
	int i=0;
	arr[i++] = *(p->firstProv);
	tProvince * aux = p->firstProv;
	while(aux->tail!=NULL){
		arr[i++]=*(aux->tail);
		aux=aux->tail;
	}
}

int addProvince(dataADT p, int id, char name[]){
	int flag = 0;
	p->firstProv=addRec(p->firstProv, id, name, &flag);
	p->total_provinces+=1; //siempre se agregara la provincia pues no se repiten
	return 1;
}

static tProvince * addRec(tProvince * firstProv ,int id, char name[], int *flag){
	int c;
	if(firstProv==NULL||(c=(strcmp(name,firstProv->name))<0)){
		tProvince * prov=calloc(1,sizeof(tProvince));
		if(prov == NULL){
			*flag = 1;
			return firstProv;}	//para no desconectar la lista
		prov->name=copyName(name);
		if(prov->name == NULL){
			*flag = 1;
		}
		prov->id=id;
		prov->tail=firstProv;
		return prov;
	}
	firstProv->tail=addRec(firstProv->tail,id,name,flag);
	return firstProv;
}

int loadProvinces(FILE * f, dataADT prov, char * separators){
	
	char * buf = malloc(BUFFER);
	if(buf == NULL)
		return ERROR;
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
				if(addProvince(prov, id, campo)==ERROR)
					return ERROR;
			}
			campo = strtok(NULL, separators);
			numCampo++;
		}

	}
	free(buf);
	return 1;
}

int loadData(FILE * f, dataADT prov, char * separators){

	char * buf = malloc(BUFFER);
	if(buf==NULL)
		return ERROR;
	int cont=0;
	int numCampo;
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
		if(addData(prov, year, id, sex) == ERROR){
			return ERROR;
		}
	}
	free(buf);
	return 1;
}

static int addData(dataADT prov, int year, int id, char sex){
	tProvince * aux = getProvince(prov, id);
	prov->total_births+=1;
	if(aux != NULL)
		aux->births+=1;
	if(addYear(prov, year, sex) == ERROR)
		return ERROR;
	return 1;
}


static tProvince * getProvince(dataADT p, int id){
    tProvince * aux=p->firstProv;
    while(aux != NULL){
        if(aux->id==id)
            return aux;       
        aux=aux->tail;
    }
    return NULL;
}

void freeAll(dataADT p){
	freeYearList(p);
	freeProvList(p);
	free(p);
}

static void freeProvList(dataADT p){
	freeRec(p->firstProv);
}

static void freeRec(tProvince * firstProv){
	if(firstProv==NULL)
		return;
	freeRec(firstProv->tail);
	free(firstProv->name);
	free(firstProv);
	
}

static void freeRecYear(tYear *firstYear){
	if(firstYear==NULL)
		return;
	freeRecYear(firstYear->tail);
	free(firstYear);
}

static void freeYearList(dataADT p){
	freeRecYear(p->firstYear);
}

void toBegin(dataADT p){
	p->currentProv=p->firstProv;
}

long int next(dataADT p, char name[]){
	long int aux=p->currentProv->births;
	copyStatic(name,p->currentProv->name);
	p->currentProv=p->currentProv->tail;
	return aux;
}

int hasNext(dataADT p){
	return p->currentProv!=NULL;
}

static int compareProvinces(const void * p1, const void * p2){
	int c2 = ((tProvince *)p2)->births;
	int c1 = ((tProvince *)p1)->births;

	int cmp = (c2 > c1) - (c2 < c1);
	if (cmp != 0)
		return cmp;
	else{
		return(strcmp(((tProvince *)p1)->name,((tProvince *)p2)->name));
	}
}

int copyPercentageData(dataADT p, FILE * f){
	fprintf(f, "Provincia;Porcentajes\n");
	tProvince * provinces = malloc((p->total_provinces) * sizeof(tProvince));
	if(provinces == NULL)
		return ERROR;
	listToArray(p, provinces);
	int i;
	for(i=0; i<p->total_provinces; i++)
		provinces[i].births = (provinces[i].births*100.0)/p->total_births;
	qsort(provinces, p->total_provinces, sizeof(tProvince), &compareProvinces);
	for(i=0 ; i<p->total_provinces ;i++){
		fprintf(f, "%s;%%%ld\n",provinces[i].name,provinces[i].births);
	}
	free(provinces);
	return 1;
}

void toBeginYear(dataADT p){
	p->currentYear=p->firstYear;
}

int nextYear(dataADT p, long int * male, long int * female){
	long int aux=p->currentYear->year;
	*male = p->currentYear->male_births;
	*female = p->currentYear->female_births;
	p->currentYear=p->currentYear->tail;
	return aux;
}

int hasNextYear(dataADT p){
	return p->currentYear!=NULL;
}

int addYear(dataADT p, int year, char sex){
	int flag=0;
	int errorcheck=0;
	p->firstYear=addRecYear(p->firstYear,year,&flag,sex,&errorcheck);
	if(errorcheck){
		return ERROR;
	}
	if(flag)
		p->total_years+=1;
	return 1;
}

static void addBySex(tYear * year, char sex){
	switch(sex-'0'){
		case 1: year->male_births+=1;break;
		case 2: year->female_births+=1;break;
		default:return;
	}
	return;
}

static tYear * addRecYear(tYear * firstYear, int year, int *flag, char sex, int *errorcheck){
	int c;
	if(firstYear==NULL || (c=year-firstYear->year)<0){
		tYear *aux=calloc(1,sizeof(tYear));
		if(aux == NULL){
			*errorcheck = 1;
			return firstYear;	//para no desconectar la lista
		}
		aux->year=year;
		aux->tail=firstYear;
		addBySex(aux, sex);
		(*flag)=1;
		return aux;
	}
	else if(c==0){
		addBySex(firstYear, sex);
		return firstYear;
	}
	firstYear->tail=addRecYear(firstYear->tail,year,flag,sex,errorcheck);
	return firstYear;
}







