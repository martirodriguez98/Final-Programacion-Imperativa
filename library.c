#include "library.h"

#define MAX_LINELENGTH 40

void query1(dataADT p){
	FILE * f = fopen("query1.csv", "w");
	fprintf(f,"Provincia;Nacimientos\n");
	long int b;
	toBegin(p);
	char name[MAX_LINELENGTH];
	while(hasNext(p)){
		b=next(p,name);
		fprintf(f,"%s;%ld\n", name,b);
		}
	fclose(f);
	return;
}

void query2(dataADT p){
	FILE * f = fopen("query2.csv", "w");
	fprintf(f,"Año;Varón;Mujer\n");
	toBeginYear(p);
	long int male, female;
	int year;
	while(hasNextYear(p)){
		year = nextYear(p, &male, &female);
		fprintf(f, "%d;%ld;%ld\n", year, male, female);
	}
	fclose(f);
	return;
}

void query3(dataADT p){
	FILE * f = fopen("query3.csv", "w");
	copyPercentageData(p, f);
	return;
}
