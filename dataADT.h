#ifndef dataADT_H
#define dataADT_H
#include <stdio.h>

typedef struct dataCDT * dataADT;

dataADT newProvList();
void addProvince(dataADT p, int id, char * name);
void loadProvincies(FILE * f, dataADT prov, char * separators);
void loadData(FILE * f, dataADT prov, char * format);
void addYear(dataADT p, int year, char sex);
void freeAll(dataADT p);
void toBegin(dataADT p);
int hasNext(dataADT p);
long int next(dataADT p, char name[]);
void copyPercentageData(dataADT p, FILE * f);
int nextYear(dataADT p, long int * male, long int * female);
void toBeginYear(dataADT p);
int hasNextYear(dataADT p);

#endif
