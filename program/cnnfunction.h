#include "cnnfunction.c"

void kuantisasi_float3d(float *data_lama, int bits,int* output,int length1, int length2, int length3,float *scale);
void kuantisasi_float1d(float *data_lama, int bits,int *output, int length1,float *scale);
void softmax(float layer_last_out[10], float *output);
void relu(float *input);
void matmul(int *quantized_d, int *quantized_w, int sizein, int sizeout, float Scale_d, float Scale_w, float *out);
void scale3D(float *input, float scale_d, float scale_w,int layer);