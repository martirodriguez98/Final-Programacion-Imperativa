#ifndef YEARADT_H
#define YEAR_H
#include <stdio.h>

typedef struct yearCDT * yearADT;

yearADT newYearList();

void addYear(yearADT y, size_t year);

size_t isEmpty(yearADT y);

void freeYearList(yearADT y);

void print(yearADT y);

