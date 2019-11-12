#include <stdio.h>
#include <string.h>
#include "my_table.h"

#define row_number_d 10
#define column_number_d 4

double date_to_double(char *date){
	double return_date;
	char year[5],month[3],day[3];
	int i=0;
	int j=0;
	int k=0;
	while(*(date+i)!='\0'){
		//printf("%c",*(date+i));
		if(j==0){
			if(*(date+i)=='/'){
				year[k]='\0';
				k=0;
				j++;
			}
			else{
				year[k]=*(date+i);
				k++;
			}
		}
		else if(j==1){
			if(*(date+i)=='/'){
				month[k]='\0';
				k=0;
				j++;
			}
			else{
				month[k]=*(date+i);
				k++;
			}
		}
		else if(j==2){
				day[k]=*(date+i);
				k++;
		}
		i++;
	}
	day[k]='\0';
	return_date=atoi(year)*10000+atoi(month)*100+atoi(day);
	//printf("%s %s %s %lf\n",year,month,day,return_date);
	return return_date;
}

double time_to_double(char *time_tt){
	double return_time;
	char hour[3],min[3],sec[3];
	int i=0;
	int j=0;
	int k=0;
	while(*(time_tt+i)!='\0'){
		//printf("%c",*(time_tt+i));
		if(j==0){
			if(*(time_tt+i)==':'){
				hour[k]='\0';
				k=0;
				j++;
			}
			else{
				hour[k]=*(time_tt+i);
				k++;
			}
		}
		else if(j==1){
			if(*(time_tt+i)==':'){
				min[k]='\0';
				k=0;
				j++;
			}
			else{
				min[k]=*(time_tt+i);
				k++;
			}
		}
		else if(j==2){
				sec[k]=*(time_tt+i);
				k++;
		}
		i++;
	}
	sec[k]='\0';
	return_time=atoi(hour)*10000+atoi(min)*100+atoi(sec);
	//printf("%s %s %s %lf\n",hour,min,sec,return_time);
	return return_time;
}

int main(void){
	int row_number;
	int column_number;
	register int i=0;
	double *rand_record;

	object *ob=(object *)malloc(sizeof(object));
	ob->top=NULL;
	ob->tail=NULL;

#if 1
	ob->column_number=4;
	//ob->column_number=1;
  FILE *input_file;
  input_file=fopen("data.txt","r");
	char date[25];
	char time_tt[25];
	double *array;
	array=(double *)malloc(sizeof(double)*ob->column_number);
	while(fscanf(input_file,"%s %s %lf %lf\n",&date,&time_tt,&array[2],&array[3])!=EOF){
			array[0]=date_to_double(date);
			array[1]=time_to_double(time_tt);
			//printf("%s %s %lf %lf\n",date,time_t,array[2],array[3]);
			ob=add_new_record(ob,array);
			array=(double *)malloc(sizeof(double)*ob->column_number);
	}
	fclose(input_file);
#endif


#if 1
	printf("source table\n");
	print_list(ob);
	printf("---------------------------------------------\n");

#endif

}
