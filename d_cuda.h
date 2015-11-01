#ifndef _D_CUDA_H_
#define _D_CUDA_H_
#include <iostream>
#include <vector>
#include <cuda_runtime.h>
#include <cuda.h>
#include <time.h>
#include "opencv2/highgui/highgui.hpp"
#pragma comment(lib, "cudart")
#include "array.h"


using std::cerr;
using std::cout;
using std::endl;
using std::exception;
using std::vector;
using std::iterator;
using namespace std;
using namespace cv;

void host_to_device_2D(int* d_MTX_1, matrix_2D MTX_1)
{
		int *in_1 = d_MTX_1;
		for (matrix_2D::iterator it = MTX_1.begin() ; it != MTX_1.end(); ++it) 
		{
			int *src = &((*it)[0]);
			size_t sz = it->size();
			cudaMemcpy(in_1, src, sizeof(int)*sz, cudaMemcpyHostToDevice);
			in_1 += sz;
		//free(src);
		}
	//free(in_1);
}

void host_to_device_1D(int* d_MTX_1, matrix_1D MTX_1)
{
		int sz;
		sz = MTX_1.size();
			cudaMemcpy( d_MTX_1, &MTX_1[0], sizeof(int)*sz, cudaMemcpyHostToDevice);			
		
}


void device_to_host_2D(int* d_MTX_1, matrix_2D &MTX_1)
{
	matrix_1D D;
	int size_d;
	size_d = MTX_1.size()*MTX_1[0].size();
	D.resize(size_d);
	cudaMemcpy(&D[0],d_MTX_1, size_d*sizeof(int), cudaMemcpyDeviceToHost);
	matrix_1D_to_2D(D,MTX_1);
	D.clear();
}


void delete_int(int* var)
{
	cudaFree(var);
}




#endif