#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"


static const char filename[] = "ECG.txt";
FILE *file;


int getNextData(){

	int i1;

	if (!file){
		file = fopen ( filename, "r" );
	}

	if(!feof(file)){
		fscanf(file,"%i",&i1);
		return i1;
	}
	else{return -100000;}



}
