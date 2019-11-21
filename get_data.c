/*
 *	Name				: get_data.c
 *	Author			: Chun-Hsiang Chao
 *	Language		: C
 *	Latest Revision	: 20191113
 */
#include<stdio.h>
#include"my_find_string.h"

int main(void){
	FILE *out;
	char *search_string=NULL;
	char *buffer;
	int i=1;
	buffer=read_file_into_buffer("log.txt");
	out=fopen("data.txt","w");
	search_string=find_between_string(buffer,"+IPD,0,28:","\n",i);
	while(search_string!=NULL){
		printf("%d %s\n",i,search_string);
		fprintf(out,"%s\n",search_string);
		i++;
		search_string=find_between_string(buffer,"+IPD,0,28:","\n",i);
	}
	fclose(out);
	return 0;
}
