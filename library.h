#ifndef LIBRARY_H
#define LIBRARY_H
#include <stdio.h>
#include "provListADT.h"

int validateFile(FILE * f);
void cargarProvincias(FILE * f, provListADT prov);

#endif
