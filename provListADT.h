#ifndef PROVLISTADT_H
#define PROVLISTADT_H
#include <stdio.h>

typedef struct provListCDT * provListADT;

provListADT newProvList();
void addProvince(provListADT p, size_t id, char * name);
void print(provListADT p); //para imprimir, despues lo borramos
void cargarProvincias(FILE * f, provListADT prov, char * format);
void cargarDatos(FILE * f, provListADT prov, char * format);
void addYear(provListADT p, size_t year, size_t sex);
size_t isEmptyYear(provListADT p);
void freeAll(provListADT p);
void printYear(provListADT p);
void toBegin(provListADT p);
int hasNext(provListADT p);
long int next(provListADT p, char name[]); 

#endif
