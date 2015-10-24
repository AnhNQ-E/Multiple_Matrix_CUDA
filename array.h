#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <vector>
#include <iostream>
#include <cuda_runtime.h>
#include <cuda.h>
#include <time.h>
#include "opencv2/highgui/highgui.hpp"
#pragma comment(lib, "cudart")
#include <vector>

using namespace std;
typedef vector<vector<int>>  matrix_2D;
typedef vector<int>  matrix_1D;


void create_size_matrix_2D(matrix_2D  &Array2D, int cols, int rows)
{
	Array2D.resize(cols);
	for(int i=0;i<cols;++i)
	Array2D[i].resize(rows);
}

void create_size_matrix_1D(matrix_1D  &Array1D, int size)
{
	Array1D.resize(size);
	
}

void fill_matrix_2D(matrix_2D  &Array2D, int value_fill)
{
	int cols, rows;
	cols = Array2D[0].size();
	rows = Array2D.size();
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			Array2D[i][j] = value_fill;
}

void rand_matrix_2D(matrix_2D  &Array2D)
{
	int cols, rows;
	cols = Array2D[0].size();
	rows = Array2D.size();
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			Array2D[i][j] = rand()/10000;
}

void show_matrix_2D(matrix_2D  &Array2D)
{
	int cols, rows;
	cols = Array2D[0].size();
	rows = Array2D.size();
	for(int i=0;i<rows;i++)
		{
			for(int j=0;j<cols;j++)
				cout<<Array2D[i][j]<<" ";
			cout<<endl;
		}
}

void info_matrix_2D(matrix_2D  &Array2D)
{
	int cols, rows;
	cols = Array2D[0].size();
	rows = Array2D.size();
	cout<<"rows: "<<rows<<"  cols:  "<<cols<<endl;
}

void matrix_1D_to_2D(matrix_1D &Array1D, matrix_2D &Array2D)
{
	int cols, rows;
	cols = Array2D[0].size();
	rows = Array2D.size();
	for(int i=0;i<rows;i++)
		{
			for(int j=0;j<cols;j++)
				Array2D[i][j] = Array1D[i*cols+j];			
		}
}
#endif