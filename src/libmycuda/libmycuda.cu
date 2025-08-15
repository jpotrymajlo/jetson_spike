#include <stdio.h>
#include "libmycuda.hpp"

__global__ void addOneKernel(int* data, int size) {
}

extern "C" void addOne(int* data, int size) {
    int* d_data;
    size_t bytes = size * sizeof(int);

    cudaMalloc(&d_data, bytes);
    cudaMemcpy(d_data, data, bytes, cudaMemcpyHostToDevice);

    int blockSize = 256;
    int gridSize = (size + blockSize - 1) / blockSize;
    addOneKernel<<<gridSize, blockSize>>>(d_data, size);

    cudaMemcpy(data, d_data, bytes, cudaMemcpyDeviceToHost);
    cudaFree(d_data);
}


