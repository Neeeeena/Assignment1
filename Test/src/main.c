#include <stdio.h>
#include "sensor.h"

int sensorData[13];
int lowpassData[33];
int highpassData[5];
int derData;
int sqData[30];
int mwiData[8]; //dont know actual size.
int sIndex = 0;
int lpIndex = 0;
int hpIndex;
int sqIndex;
int mwiIndex;


int main() {


	while((sensorData[sIndex%13] = getNextData())!=-1){
		lowPass();

		highPass();

		derivative();

		squaring();

		mwi();

		sIndex++; //last
	}
	return 0;
}

int lowPass(){

	int i = sIndex%13;
	//printf("%d\n",i);

	int temp = 2*lowpassData[(lpIndex-1)%33]-lowpassData[(lpIndex-2)%33]+(float)1/32*(sensorData[i]-2*sensorData[(i+7)%13]+sensorData[(i+1)%13]);
	lowpassData[(lpIndex)%33] = temp;
	//printf("lowpass result: %d,\n",temp);

	//printf("y result: %d\n",lowpassData[(lpIndex-1)%33]);
	//printf("lowpass: %d: %d, %d: %d, %d: %d\n", i, sensorData[i], (i+7)%13, sensorData[(i+7)%13], (i+1)%13, sensorData[(i+1)%13]);

	return 0;


}

int highPass(){
	int i = lpIndex%33;

	int temp = highpassData[(hpIndex-1)%5] - (float) lowpassData[i]/32 + lowpassData[(i+17)%33] - lowpassData[(i+16)%33] + (float)lowpassData[(i+1)%33]/32;
	highpassData[(hpIndex)%5] = temp;
	//printf("i: %d, minus16: %d, minus17: %d, minus32: %d\n", i, (i+17)%33, (i+16)%33, (i+1)%33);
	printf("highpass: %d\n",temp);

	lpIndex++;

	return 0;

}

int derivative(){
	int i = hpIndex%5;

	derData = (float)1/8*(2*highpassData[i] + highpassData[(i+4)%5] - highpassData[(i+2)%5] - 2*highpassData[(i+1)%5]);
	hpIndex++;
	//printf("der: %d\n", derData);

	return 0;
}

int squaring(){

	sqData[sqIndex%30] = derData*derData;
	//printf("sq: %d\n", sqData[sqIndex%30]);

	return 0;
}

int mwi(){
	int sum = 0;
	for(int i = 0; i<30; i++){
		sum += sqData[i];
	}
	mwiData[(mwiIndex)%8] = (float)1/30*sum;
	//printf("done: %d\n", mwiData[(mwiIndex)%8]);


	return 0;

}


