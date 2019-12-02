
static void copyName(tProvince * prov, char * name){
	int i=0;
	prov->name=NULL;
	while(name[i]!=0){
		if(i%BLOQUE==0){
			prov->name=realloc(prov->name,i+BLOQUE);
		}
		prov->name[i]=name[i];
		i++;
	}
	prov->name=realloc(prov->name,i);
	prov->name[i]=0;
}