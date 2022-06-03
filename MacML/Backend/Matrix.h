#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <stdlib.h>	

// TODO: Consider moving away from dynamic arrays and towards 2d vectors.  Prevent memory leaks & clean up some bits of code
class Matrix
{

private:

	int rows;
	int cols;
	float** matrix;

	bool checkRange(int row, int col);

public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, float** data);

	static Matrix makeRow(int columns, float* data);
	static Matrix makeColumn(int rows, float* data);

	~Matrix();

	void randomize(float min, float max);
	
	void set(int row, int col, float value);
	float get(int row, int col);

	float* getRow(int row);
	float* getCol(int col);

	int getRows();
	int getCols();

	Matrix transposed();

	void print();
};
