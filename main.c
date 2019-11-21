/*
 *	Name				: main.c
 *	Author			: Chun-Hsiang Chao
 *	Language		: C
 *	Latest Revision	: 20191113
 */
#include <stdio.h>
#include <string.h>
#include "my_table.h"
#include "gd.h"

#define row_number_d 10
#define column_number_d 4

#define PI 3.141592
#define DELTA (PI/8)

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
	int chart_x_number=20;
	int chart_y_number=18;
  /* Declare the image */
  gdImagePtr im;
  /* Declare output files */
  FILE *pngout, *jpegout;
  /* Declare color indexes */
	int brect[8];
	char font[]="/usr/share/fonts/truetype/Noto_Serif_TC/NotoSerifTC-Light.otf";
  int black;
  int white;
	int green;
	int red;
	int point_x,point_y;
	char temp[30];
	int i;

	object *ob=(object *)malloc(sizeof(object));
	ob->top=NULL;
	ob->tail=NULL;

	list *ob_point;
	double time_min,time_max;

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
	//print_list(ob);
	printf("---------------------------------------------\n");
#endif

  im = gdImageCreate(800, 800);
  black = gdImageColorAllocate(im, 0, 0, 0);  
  white = gdImageColorAllocate(im, 255, 255, 255);  
	red = gdImageColorAllocate(im, 255, 0, 0);	
	green = gdImageColorAllocate(im, 0, 255, 0);	
	gdImageFilledRectangle(im, 0, 0,799,799, white);	
  gdImageLine(im, 99, 699, 699, 699, black);  
  gdImageLine(im, 99, 99, 99, 699, black);  

	gdImageStringFT(im, brect, black, font, 24, DELTA*0, 399, 749,"Time");
	gdImageStringFT(im, brect, black, font, 24, DELTA*4, 49, 399,"Voltage");

	time_min=ob->top->record[1];
	time_max=ob->tail->record[1];
	printf("%lf\n",time_min);
	printf("%lf\n",time_max);
	printf("%d\n",ob->row_number);
	printf("%lf\n",ob->top->record[2]);
	printf("%lf\n",ob->top->record[3]);

	ob_point=ob->top;
	for(i=0;i<chart_x_number;i++){
		if(ob_point==NULL) break;
		sprintf(temp,"%.0lf",ob_point->record[1]);
		gdImageStringFT(im, brect, red, font, 24, DELTA*(-3), 99+30*i, 699,temp);


		gdImageFilledEllipse(im,99+20+30*i,710-12-35*ob_point->record[2],20,20,black);
		ob_point=ob_point->down;
	}


	for(i=0;i<chart_y_number;i++){
		sprintf(temp,"%d",i);
		gdImageStringFT(im, brect, red, font, 24, DELTA*(0), 59, 710-35*i,temp);
	}

#if 0	
	gdImageFilledEllipse(im,400,400,30,30,black);
	gdImageFilledRectangle(im, 400, 400,799,799, white);	
	gdImageRectangle(im, 200, 200,300,200, black);
	
	gdImageSetThickness(im, 5);
	gdImageLine(im,300,300,400,300,black);
	gdImageSetThickness(im, 20);
	gdImageSetAntiAliased(im,  red);
	gdImageLine(im,300,330,400,330,gdAntiAliased);
	gdImageDashedLine(im,300,350,400,350,black);
	gdImageEllipse(im,200,200,60,60,black);
	gdImageStringFT(im, brect, black, font, 24, DELTA*0, 300, 300,"ABC中文");
#endif
  pngout = fopen("test.png", "wb");
  gdImagePng(im, pngout);
  fclose(pngout);
  gdImageDestroy(im);


}
