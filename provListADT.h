#ifndef PROVLISTADT_H
#define PROVLISTADT_H
#include <stdio.h>

typedef struct provListCDT * provListADT;

provListADT newProvList();//crea la lista de provincias y años
void addProvince(provListADT p, int id, char * name); //agrega la provincia con su id
void print(provListADT p); //para imprimir, despues lo borramos
void cargarProvincias(FILE * f, provListADT prov, char * separators); //carga las provincias obtenidas desde el archivo .csv, linea por linea
void cargarDatos(FILE * f, provListADT prov, char * format);  //carga en las provincias y años los nacimientos leidos desde el archivo .csv
void addYear(provListADT p, int year, char sex);   //añade un nacimiento al año indicado, y crea el año en la lista si es necesario
size_t isEmptyYear(provListADT p);  
void freeAll(provListADT p);  //libera la lista de años y provincias
void printYear(provListADT p);
void toBegin(provListADT p);  //funciones para iterar sobre la lista de provincias
int hasNext(provListADT p);
long int next(provListADT p, char name[]);
void copyPercentageData(provListADT p, FILE * f); //copia al archivo csv los porcentajes de nacimientos de cada provincia
int nextYear(provListADT p, long int * male, long int * female);   //funciones para iterar sobre la lista de años
void toBeginYear(provListADT p);
int hasNextYear(provListADT p);

#endif
