#include "Matrix.h"

using namespace std;

Matrix::Matrix()
{
	Matrix::rows = 0;
	Matrix::cols = 0;
	Matrix::matrix = new float* [0];
	Matrix::matrix[0] = new float[0];
	Matrix::matrix[0][0] = 0;
}

Matrix::Matrix(int rows, int cols)
{
	Matrix::rows = rows;
	Matrix::cols = cols;
	Matrix::matrix = new float* [rows];

	for (int i = 0; i < rows; i++)
	{
		Matrix::matrix[i] = new float[cols];
		for (int j = 0; j < cols; j++)
		{
			Matrix::matrix[i][j] = 0;
		}
	}
}

// TODO: Learn if there's a better way to copy dynamic arrays
Matrix::Matrix(int rows, int cols, float** data)
{
	Matrix::rows = rows;
	Matrix::cols = cols;
	Matrix::matrix = new float* [rows];

	for (int i = 0; i < rows; i++)
	{
		Matrix::matrix[i] = new float[cols];
		for (int j = 0; j < cols; j++)
		{
			Matrix::matrix[i][j] = data[i][j];
		}
	}
}

Matrix Matrix::makeRow(int columns, float* data)
{
	// Make a single-row matrix from a 1d array
	Matrix m = Matrix(1, columns);
	for (int i = 0; i < columns; i++)
	{
		m.set(0, i, data[i]);
	}

	return m;
}

Matrix Matrix::makeColumn(int rows, float* data)
{
	// Make a single-column matrix from a 1d array
	Matrix m = Matrix(rows, 1);
	for (int i = 0; i < rows; i++)
	{
		m.set(i, 0, data[i]);
	}

	return m;
}

Matrix::~Matrix()
{
	delete[] Matrix::matrix;
}

void Matrix::randomize(float min, float max)
{
	for (int i = 0; i < Matrix::rows; i++)
	{
		for (int j = 0; j < Matrix::cols; j++)
		{
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			Matrix::matrix[i][j] = r * (max - min) + min;
		}
	}
}

void Matrix::set(int row, int col, float value)
{
	if (Matrix::checkRange(row, col))
		Matrix::matrix[row][col] = value;
}

float Matrix::get(int row, int col)
{
	if (Matrix::checkRange(row, col))
		return Matrix::matrix[row][col];
	
	return 0;
}

float* Matrix::getRow(int row)
{
	return Matrix::matrix[row];
}

float* Matrix::getCol(int col)
{
	float* column = new float[Matrix::rows];
	for (int i = 0; i < Matrix::rows; i++)
	{
		column[i] = Matrix::matrix[i][col];
	}

	return column;
}

int Matrix::getRows()
{
	return Matrix::rows;
}

int Matrix::getCols()
{
	return Matrix::cols;
}

Matrix Matrix::transposed()
{
	Matrix t = Matrix(Matrix::cols, Matrix::rows);

	for (int i = 0; i < Matrix::rows; i++)
	{
		for (int j = 0; j < Matrix::cols; j++)
		{
			t.set(j, i, Matrix::matrix[i][j]);
		}
	}

	return t;
}

bool Matrix::checkRange(int row, int col)
{
	if (row >= Matrix::rows)
	{
		cout << "ERROR: Row must be within the matrix's range" << endl;
		return false;
	}

	if (col >= Matrix::cols)
	{
		cout << "ERROR: Column must be within the matrix's range" << endl;
		return false;
	}

	return true;
}

void Matrix::print()
{
	for (int i = 0; i < Matrix::rows; i++)
	{
		for (int j = 0; j < Matrix::cols; j++)
		{
			float rounded = roundf(Matrix::matrix[i][j] * 100) / 100;
			cout << rounded << ", ";
		}
		cout << endl;
	}

	cout << endl;
}