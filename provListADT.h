#ifndef PROVLISTADT_H
#define PROVLISTADT_H
#include <stdio.h>

typedef struct provListCDT * provListADT;

provListADT newProvList();
void addProvince(provListADT p, int id, char * name);
void print(provListADT p); //para imprimir, despues lo borramos
void cargarProvincias(FILE * f, provListADT prov, char * separators);
void cargarDatos(FILE * f, provListADT prov, char * format);
void addYear(provListADT p, int year, char sex);
size_t isEmptyYear(provListADT p);
void freeAll(provListADT p);
void printYear(provListADT p);
void toBegin(provListADT p);
int hasNext(provListADT p);
long int next(provListADT p, char name[]);
void copyPercentageData(provListADT p, FILE * f);
int nextYear(provListADT p, long int * male, long int * female);
void toBeginYear(provListADT p);
int hasNextYear(provListADT p);

#endif
