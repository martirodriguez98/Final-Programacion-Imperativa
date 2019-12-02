#ifndef PROVLISTADT_H
#define PROVLISTADT_H
#include <stdio.h>

typedef struct provListCDT * provListADT;

provListADT newProvList();
void addProvince(provListADT p, size_t id, char * name);
void freeProvList(provListADT p);
void print(provListADT p); //para imprimir, despues lo borramos

#endif
