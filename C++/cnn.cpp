#include "cnn.h"
#include <cmath>

float relu(float x) {
    return x > 0 ? x : 0;
}

float sigmoid(float x) {
    return 1 / (1 + exp(-x));
}

void conv2d(float *input, float *output, const float weights[], const float biases[], int filters, int kernel_size, int image_size) {
    for (int f = 0; f < filters; ++f) {
        for (int i = 0; i < image_size; ++i) {
            for (int j = 0; j < image_size; ++j) {
                float sum = biases[f];
                for (int ki = 0; ki < kernel_size; ++ki) {
                    for (int kj = 0; kj < kernel_size; ++kj) {
                        int x = i + ki - kernel_size / 2;
                        int y = j + kj - kernel_size / 2;
                        if (x >= 0 && x < image_size && y >= 0 && y < image_size) {
                            sum += *(input+x*image_size+y)* weights[f * kernel_size * kernel_size + ki * kernel_size + kj];
                        }
                    }
                }
                *(output+i*image_size+j) = relu(sum);
            }
        }
    }
}

void maxpooling2d(float *input, float *output, int pool_size, int image_size) {
    for (int i = 0; i < image_size / 2; ++i) {
        for (int j = 0; j < image_size / 2; ++j) {
            float max_val = -1e9;
            for (int pi = 0; pi < pool_size; ++pi) {
                for (int pj = 0; pj < pool_size; ++pj) {
                    int x = i * pool_size + pi;
                    int y = j * pool_size + pj;
                    if (x < image_size && y < image_size) {
                        max_val = std::max(max_val, *(input+x*image_size+y));
                    }
                }
            }
            *(output+i*image_size+j) = max_val;
        }
    }
}

void dense(float input[], float output[], const float weights[], const float biases[], int units) {
    for (int i = 0; i < units; ++i) {
        float sum = biases[i];
        for (int j = 0; j < IMG_SIZE * IMG_SIZE / 64; ++j) {
            sum += input[j] * weights[i * (IMG_SIZE * IMG_SIZE / 64) + j];
        }
        output[i] = relu(sum);
    }
}

float cnn(float input_image[IMG_SIZE][IMG_SIZE]) {
    float conv1_output[IMG_SIZE][IMG_SIZE];
    float pool1_output[IMG_SIZE / 2][IMG_SIZE / 2];
    float conv2_output[IMG_SIZE / 2][IMG_SIZE / 2];
    float pool2_output[IMG_SIZE / 4][IMG_SIZE / 4];
    float conv3_output[IMG_SIZE / 4][IMG_SIZE / 4];
    float pool3_output[IMG_SIZE / 8][IMG_SIZE / 8];
    float flatten_output[IMG_SIZE * IMG_SIZE / 64];
    float dense1_output[DENSE_UNITS];
    float final_output = 0;

    float * ptro_image = &(input_image[0][0]);

    conv2d(ptro_image, &(conv1_output[0][0]), conv2d_weights, conv2d_biases, CONV1_FILTERS, 3, IMG_SIZE);
    float * ptro_conv1_output = &(conv1_output[0][0]);
    maxpooling2d(ptro_conv1_output, &(pool1_output[0][0]), 2, IMG_SIZE);

    float * ptro_pool1_output = &(pool1_output[0][0]);

    conv2d(ptro_pool1_output,  &(conv2_output[0][0]), conv2d_1_weights, conv2d_1_biases, CONV2_FILTERS, 3, IMG_SIZE/2);
    float * ptro_conv2_output = &(conv2_output[0][0]);
    maxpooling2d(ptro_conv2_output, &(pool2_output[0][0]), 2, IMG_SIZE/2);

    float * ptro_pool2_output = &(pool2_output[0][0]);

    conv2d(ptro_pool2_output,  &(conv3_output[0][0]), conv2d_2_weights, conv2d_2_biases, CONV3_FILTERS, 3, IMG_SIZE/4);
    float * ptro_conv3_output = &(conv3_output[0][0]);
    maxpooling2d(ptro_conv3_output, &(pool3_output[0][0]), 2, IMG_SIZE/4);

    int index = 0;
    for (int i = 0; i < IMG_SIZE / 8; ++i) {
        for (int j = 0; j < IMG_SIZE / 8; ++j) {
            flatten_output[index++] = pool3_output[i][j];
        }
    }

    dense(flatten_output, dense1_output, dense_weights, dense_biases, DENSE_UNITS);
    dense(dense1_output, &final_output, dense_1_weights, dense_1_biases, 1);

    return sigmoid(final_output);
}