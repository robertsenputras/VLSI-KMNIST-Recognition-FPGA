#include <stdio.h>
#include <math.h>

int data_lama[num_input];

void kuantisasi_integer(int data_lama[], int bits){
	int max, min, temp;
	int range_real;
	float range_real;
	int data_baru[num_input];
	
	temp = 0;
	
	for ( i =0; i< num_input; i++){
		if (data[i] > temp) 
			max = data[i];
			temp = data[i];
	}
	temp = 0;
	for ( i = 0; i < num_input; i++ ){
		if (data[i] < temp)
			min = data[i];
			temp = data[i];
	}
	
	range_real = max - min;
	
	if (range_real == 0)
        range_real = 1
			
	scale = ((range_real/pow(2,bits))-1);
	
	for ( i = 0 ; i < num_input; i++){
		databaru[i] = round(datalama[i]/scale);
	}
	
}

void kuantisasi_float(float data_lama[], int bits){
	float max, min, temp;
	float range_real;
	float range_real;
	int data_baru[num_input];
	
	temp = 0;
	
	for ( i =0; i< num_input; i++){
		if (data_lama[i] > temp) 
			max = data_lama[i];
			temp = data_lama[i];
	}
	temp = 0;
	for ( i = 0; i < num_input; i++ ){
		if (data_lama[i] < temp)
			min = data_lama[i];
			temp = data_lama[i];
	}
	
	range_real = max - min;
	
	if (range_real == 0)
        range_real = 1
			
	scale = ((range_real/pow(2,bits))-1);
	
	for ( i = 0 ; i < num_input; i++){
		databaru[i] = round(data_lama[i]/scale);
	}
	
}

	