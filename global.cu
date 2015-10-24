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
#include "multiple.h"


using std::cerr;
using std::cout;
using std::endl;
using std::exception;
using std::vector;
using std::iterator;


using namespace std;
using namespace cv;
// CUDA kernel: adds each array value

#define size 8

int main(void)
{
	//////////////////////////////// INIT /////////////////////////
	
	matrix_2D A,B,C;		
	unsigned int mem_size_C = sizeof(int) * size*size;
	create_size_matrix_2D(A,size,size);
	create_size_matrix_2D(B,size,size);
	create_size_matrix_2D(C,size,size);

	info_matrix_2D(A);
	rand_matrix_2D(A);
	show_matrix_2D(A);

	info_matrix_2D(B);
	rand_matrix_2D(B);
	show_matrix_2D(B);

	info_matrix_2D(C);
	fill_matrix_2D(C,0);
	//show_matrix_2D(C);
	
	int *da ,*db ,* dc;
	cudaMalloc (( void **) & dc , size*size* sizeof ( int ));
	cudaMalloc (( void **) & db , size*size* sizeof ( int ));
	cudaMalloc (( void **) & da , size*size* sizeof ( int ));

	host_to_device(da,A);
	host_to_device(db,B);

	// setup execution parameters
   int numThreadsPerBlock = size;
   int numBlocks = (size * size);
   int sharedMemSize = numThreadsPerBlock * sizeof(int);

   dim3 dimGrid(numBlocks);
   dim3 dimBlock(numThreadsPerBlock);

   // execute the kernel
   matrixMul <<< dimGrid, dimBlock, sharedMemSize >>>(da, db, dc);
   
   //Block until device has completed
   cudaThreadSynchronize();
   device_to_host(dc,C);
   show_matrix_2D(C);


	cudaFree ( dc) ; cudaFree ( da); cudaFree ( db);

	A.clear();
	B.clear();
	C.clear();

	
  system("PAUSE");    
}