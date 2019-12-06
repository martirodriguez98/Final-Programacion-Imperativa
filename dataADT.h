#ifndef dataADT_H
#define dataADT_H
#include <stdio.h>

typedef struct dataCDT * dataADT;

dataADT newProvList();//crea la lista de provincias y años
void addProvince(dataADT p, int id, char * name);//agrega la provincia con su id
void loadProvincies(FILE * f, dataADT prov, char * separators);//carga las provincias obtenidas desde el archivo .csv, linea por linea
void loadData(FILE * f, dataADT prov, char * format);//carga en las provincias y años los nacimientos leidos desde el archivo .csv
void addYear(dataADT p, int year, char sex);//añade un nacimiento al año indicado, y crea el año en la lista si es necesario
void freeAll(dataADT p);//libera la lista de años y provincias
void toBegin(dataADT p);//funciones para iterar sobre la lista de provincias
int hasNext(dataADT p);
long int next(dataADT p, char name[]);
void copyPercentageData(dataADT p, FILE * f);//copia al archivo csv los porcentajes de nacimientos de cada provincia
int nextYear(dataADT p, long int * male, long int * female);//funciones para iterar sobre la lista de años
void toBeginYear(dataADT p);
int hasNextYear(dataADT p);

#endif
