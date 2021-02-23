#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "weights.h"
#include "cnnfunction.h"
#include "data.h"       //untuk simulasi

int main(void)
{
    //Output Layer
    float layer_3_out[64];
    float layer_last_out[10];
    float result[10];
    int hasil;
    float max_hasil=0;
    //Konstanta pengali untuk output layer sebelum masuk kuantisasi  untuk input testing gambar 3
    float Scale_w1 =0.0032400540479524866;
    float Scale_d1 =0.007874015748031496;
    float Scale_w2 =0.004680760732785923;
    float Scale_d2=0;
    float Scale_w3 =0.006520035698657899;
    float Scale_d3=0;
    float Scale_w4 =0.005369161526987872;
    float Scale_d4=0;
    //Variabel input layer terkuantisasi
    //sebelum masuk layer 2
    int quantized_d2[6*13*13];
    int quantized_d3[150];      //sebelum masuk layer 3
    int quantized_d4[64];       //sebelum masuk layer 4
    float flat[150];
    int i,j,k;
    //Keluaran layer 1 dari HW (abis max pooling) masuk ke pengali skala
    scale3D(layer_1_out,Scale_d1,Scale_w1,1);
    // Kuantisasi Output Layer 2
    kuantisasi_float3d(layer_1_out,7,quantized_d2,6,13,13,&Scale_d2);
    // Passing ke HW hasil kuantisasi
    // Keluaran layer 2 dari HW (abis max pooling) masuk ke pengali skala
    scale3D(layer_2_out,Scale_d2,Scale_w2,2);
    int count=0;
    //Flatten        
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            for(k=0;k<6;k++){
                flat[count] = layer_2_out[i*5+j+k*25];
                count++;
            }
        }
    }
    //Quantize Flatten
    kuantisasi_float1d(flat,7,quantized_d3,150,&Scale_d3);
    //Perhitungan Layer 3 (Dense 1)
    matmul(quantized_d3,quantized_w3,150,64,Scale_d3,Scale_w3,layer_3_out);
    //Kuantisasi Output Layer 3
    kuantisasi_float1d(layer_3_out,7,quantized_d4,64,&Scale_d4);
    //Perhitungan Layer Output (Dense 2)
    matmul(quantized_d4,quantized_w4,64,10,Scale_d4,Scale_w4,layer_last_out);
    softmax(layer_last_out,result);
    printf("\nProbabilitas setiap kelas :\n");
    for(i=0;i<10;i++){
        if(result[i] > max_hasil){
            hasil = i;
            max_hasil = result[i];
        }
        printf("Kelas ke-%d : ",i);
        printf("%.4f\n", result[i]);
    }
    printf("Jadi gambar ini di klasifikasikan menjadi kelas = %d\n",hasil);
}