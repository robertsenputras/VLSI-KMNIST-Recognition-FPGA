#include <math.h>
//Fungsi kuantisasi untuk matriks 3 dimensi
void kuantisasi_float3d(float *data_lama, int bits,int* output,int length1, int length2, int length3,float *scale){
	float max, min, temp;
	float range_real;
	int data_baru;
	int l,m,n;
    // float scale;
    max = 0;
    min = 9999;
    //Cari maksimum
	for ( l =0; l<length1; l++){
        for ( m =0; m<length2; m++){
            for(n=0;n<length3;n++){
                if (*(data_lama + n + (m*length3) + (l*length2*length3)) > max){ 
                    max = *(data_lama + n + (m*length3) + (l*length2*length3));
                }
            }
        }
	}
    //Cari minimum
	for ( l =0; l<length1; l++){
        for ( m =0; m<length2; m++){
            for(n=0;n<length3;n++){
                if (*(data_lama + n + (m*length3) + (l*length2*length3)) < min){ 
                    min = *(data_lama + n + (m*length3) + (l*length2*length3));
                }
            }
        }
	}
    //Cari Range
	range_real = max - min;
	if (range_real == 0)
    {
        range_real = 1;
    }
    //Cari Skala
	*(scale) = (range_real/(pow(2,bits)-1));
    //Kuantisasi
	for ( l =0; l<length1; l++){
        for ( m =0; m<length2; m++){
            for(n=0;n<length3;n++){
		        *(output + n + (m*length3) + (l*length2*length3)) = round(*(data_lama + n + (m*length3) + (l*length2*length3))/(*(scale)));
	        }
        }
	}
}

//Fungsi untuk kuantisasi matriks 1 dimensi (sesudah flattening)
void kuantisasi_float1d(float *data_lama, int bits, int *output, int length1,float *scale){
	float max, min;
	float range_real;
	int data_baru;
	int l,m,n;
    // float scale;
    max = 0;
    min = 9999;
    //Cari maximum
	for (l=0;l<length1;l++){
        if (*(data_lama + l) > max){ 
            max = *(data_lama + l);
        }
	}
	for ( l=0;l<length1; l++){
        if (*(data_lama + l)< min){ 
            min = *(data_lama + l);
        }
	}
    //Cari Range
	range_real = max - min;
	if(range_real == 0){
        range_real = 1;
    }
    //Cari Skala
	*(scale) = (range_real/(pow(2,bits)-1));
	//Kuantisasi
	for ( l =0; l<length1; l++){
        *(output + l) = round(*(data_lama + l)/(*(scale)));
	}
}

//Fungsi softmax
void softmax(float layer_last_out[10], float *output){
    float expo[10]= {0};
    float expo_sum=0;
    for(int i = 0;i<10;i++){
        expo[i]=exp(layer_last_out[i]);
        expo_sum += expo[i];
    }
    for(int i = 0;i<10;i++){
        *(output + i) = expo[i]/expo_sum;
    }
}

//Fungsi Rectifier Linear Unit
void relu(float *input){
    if(*input<0){
        *input=0;
    }
}

//Fungsi Matrix Multiplication
void matmul(int *quantized_d, int *quantized_w, int sizein, int sizeout, float Scale_d, float Scale_w, float *out){
    int i,j;
    for(i=0;i<sizeout;i++){
        float temp = 0;
        for(j=0;j<sizein;j++){
            temp = temp + (*(quantized_d + j) * *(quantized_w + i + (j * sizeout)));
        }
        if(sizein == 150){   
            relu(&temp);
            *(out + i) = temp * Scale_d * Scale_w;
        }
        else{
            *(out + i) =  temp * Scale_d * Scale_w;
        }
    }
}

//Fungsi Perkalian Skalar 
void scale3D(float *input, float scale_d, float scale_w,int layer){
    int l,m,n;
    int length1,length2,length3;
    if (layer == 1){
        length1= 6;
        length2= 13;
        length3= 13;
    }
    else if(layer ==2){
        length1= 6;
        length2= 5;
        length3= 5;
    }
    for(l=0;l<length1;l++){
        for(m=0;m<length2;m++){
            for(n=0;n<length3;n++){
                *(input + n + (m*length3) + (l*length3*length2)) = *(input + n + (m*length3) + (l*length3*length2)) * scale_d * scale_w;
            }
        }
    }
}