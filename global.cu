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
#define col1 8
#define col2 3
#define row1 3
#define row2 8

int main(void)
{
	//////////////////////////////// INIT /////////////////////////
	
	matrix_2D A,B,C;		
	matrix_1D D,E;
	create_size_matrix_2D(A,row1,col1);
	create_size_matrix_2D(B,row2,col2);
	create_size_matrix_2D(C,row1,col2);

	D.resize(row1*col1);
	E.resize(col2*row2);
	
	info_matrix_2D(A);
	rand_matrix_2D(A);
	show_matrix_2D(A);

	info_matrix_2D(B);
	rand_matrix_2D(B);
	show_matrix_2D(B);

	info_matrix_2D(C);
	fill_matrix_2D(C,0);
	show_matrix_2D(C);
	cout<<endl<<endl;
	matrix_2D_to_1D_A(D,A);
	matrix_2D_to_1D_B(E,B);
	for(int i=0; i< row1*col1; i++)
		cout<<D[i]<<" ";
	cout<<endl;
	for(int i=0; i< row2*col2; i++)
		cout<<E[i]<<" ";
	cout<<endl;
	
	int *da ,*db ,* dc;
	cudaMalloc (( void **) & da , col1*row1* sizeof ( int ));
	cudaMalloc (( void **) & db , col2*row2* sizeof ( int ));
	cudaMalloc (( void **) & dc , row1*col2* sizeof ( int ));

	//host_to_device_2D(da,A);
	//host_to_device_2D(db,B);

	// setup execution parameters
	host_to_device_1D(da,D);	host_to_device_1D(db,E);	MatrixMulKernel<<<col2,row1>>>(da,db,dc,row2,col2,row1);
   
   //Block until device has completed
   
   device_to_host_2D(dc,C);
   cout<<endl;
   show_matrix_2D(C);
   

	cudaFree ( dc) ; cudaFree ( da); cudaFree ( db);
	
	A.clear();
	B.clear();
	C.clear();

	
  system("PAUSE");    
}