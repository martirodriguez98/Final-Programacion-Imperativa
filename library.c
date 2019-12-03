#include "library.h"
#define MAX_LINELENGTH 40
void query1(provListADT p){
	FILE * f = fopen("query1.csv", "w");
	fprintf(f,"Provincia;Nacimientos\n");
	long int b;
	toBegin(p);
	char name[MAX_LINELENGTH];
	while(hasNext(p)){
		b=next(p,name);
		printf("%s", name);
		fprintf(f,"%s;", name);
		fprintf(f,"%ld\n", b);
		}
	fclose(f);
	return;
}




