#ifndef CNN_H
#define CNN_H

#include "conv2d.h"
#include "conv2d_1.h"
#include "conv2d_2.h"
#include "dense.h"
#include "dense_1.h"

#define IMG_SIZE 100
#define CONV1_FILTERS 32
#define CONV2_FILTERS 64
#define CONV3_FILTERS 128
#define DENSE_UNITS 100

float relu(float x);
float sigmoid(float x);
void conv2d(float *input, float *output, const float weights[], const float biases[], int filters, int kernel_size, int image_size);
void maxpooling2d(float *input, float *output, int pool_size, int image_size);
void dense(float input[], float output[], const float weights[], const float biases[], int units);
float cnn(float input_image[IMG_SIZE][IMG_SIZE]);

#endif