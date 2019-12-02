
static char * copyName(char * name){
	int i=0;
	char * aux=NULL;
	while(name[i]!=0){
		if(i%BLOQUE==0){
			aux=realloc(aux,i+BLOQUE);
		}
		aux[i]=name[i];
		i++;
	}
	aux=realloc(aux,i);
	aux[i]=0;
	return aux;
}
