#ifndef _MULTIPLE_H_
#define _MULTIPLE_H_

#include <iostream>
#include <vector>
#include <cuda_runtime.h>
#include <cuda.h>
#include <time.h>
#include "opencv2/highgui/highgui.hpp"
#pragma comment(lib, "cudart")

#include <math.h>
#include <stdio.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include "array.h"
#include "d_cuda.h"


using std::cerr;
using std::cout;
using std::endl;
using std::exception;
using std::vector;
using std::iterator;


using namespace std;
using namespace cv;

__global__ void matrixMul( int *DA, int *DB, int *DC)
{   
    int bx = blockIdx.x; // Block index
    int tx = threadIdx.x; // Thread index
    int ts = blockDim.x; // number of threads   
    // Declaration of the shared memory C element
    extern __shared__ int c_element_sum[];
    c_element_sum[tx] = DA[tx+((bx/ts)*ts)] * DB[(bx%ts)+(tx*ts)];

    //Block until all threads in the block have written their data to shared mem
    __syncthreads();

    int sum;
    for(int i=0; i<ts; i++){
        if(i==0){
            sum=c_element_sum[i];
        }
        else{
            sum+=c_element_sum[i];
        }
    }
    DC[bx] = sum;

}

__global__ void MatrixMulKernel(int* Md, int* Nd, int* Pd, int thr, int col, int row)
{
// 2D Thread ID
int tx = threadIdx.x; // 
int bx = blockIdx.x;  // 
// Pvalue stores the Pd element that is computed by the thread
int Pvalue = 0;

for (int k = 0; k < thr; k++)
{
Pvalue += Md[tx * thr + k] * Nd[k + bx*thr];
}
// Write the matrix to device memory each thread writes one element
Pd[tx*col+bx] = Pvalue;
}

__global__ void add(int *da,	int *db,	int *dc){
	int index = threadIdx.x + blockIdx.x * blockDim.x;
	dc[index] = da[index] + db[index];

	__syncthreads();
}
#endif