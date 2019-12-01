#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct provListCDT * provListADT;

provListADT newProvList();
void addProvince(provListADT p, size_t id, char * name);
void freeProvList(provListADT p);
void print(provListADT p); //para imprimir, despues lo borramos
