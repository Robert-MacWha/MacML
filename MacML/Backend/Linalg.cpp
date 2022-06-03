#include "Linalg.h"

using namespace std;

Matrix Linalg::scale(Matrix m, float f)
{
	// Multiply a matrix by a scalar element-wise
	int rows = m.getRows();
	int cols = m.getCols();
	Matrix out = Matrix(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			out.set(i, j, m.get(i, j) * f);
		}
	}

	return out;
}

Matrix Linalg::dot(Matrix m1, Matrix m2)
{
	// Calculate the dot product of two matrices
	int r1 = m1.getRows();
	int c1 = m1.getCols();
	int r2 = m2.getRows();
	int c2 = m2.getCols();

	if (c1 != r2)
	{
		cout << "ERROR: Matrix indices do not match, dot product can not be calcuated" << endl;
		return Matrix(0, 0);
	}

	int rows = r1;
	int cols = c2;

	Matrix out = Matrix(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			float value = 0;

			for (int k = 0; k < c1; k++)
			{
				value += m1.get(i, k) * m2.get(k, j);
				out.set(i, j, value);
			}
		}
	}

	return out;
}

Matrix Linalg::apply(Matrix m, float (*func)(float))
{
	// Apply a given function to the matrix element-wise
	int rows = m.getRows();
	int cols = m.getCols();
	Matrix out = Matrix(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			out.set(i, j, func(m.get(i, j)));
		}
	}

	return out;
}

Matrix Linalg::multiply(Matrix m1, Matrix m2)
{
	// Multiply two matrices element-wise
	if (!Linalg::checkEquality(m1, m2))
		return Matrix();

	int rows = m1.getRows();
	int cols = m2.getCols();
	Matrix out = Matrix(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			out.set(i, j, m1.get(i, j) * m2.get(i, j));
		}
	}

	return out;
}

Matrix Linalg::add(Matrix m1, Matrix m2)
{
	// Add two matrices element-wise
	if (!Linalg::checkEquality(m1, m2))
		return Matrix();
	
	int rows = m1.getRows();
	int cols = m2.getCols();
	Matrix out = Matrix(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			out.set(i, j, m1.get(i, j) + m2.get(i, j));
		}
	}

	return out;
}

Matrix Linalg::sub(Matrix m1, Matrix m2)
{
	// Subtract two matrices element-wise
	if (!Linalg::checkEquality(m1, m2))
		return Matrix();

	int rows = m1.getRows();
	int cols = m2.getCols();
	Matrix out = Matrix(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			out.set(i, j, m1.get(i, j) - m2.get(i, j));
		}
	}

	return out;
}

Matrix Linalg::addScalar(Matrix m, float f)
{
	// Add a scaler to a matrix element-wise
	int rows = m.getRows();
	int cols = m.getCols();
	Matrix out = Matrix(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			out.set(i, j, m.get(i, j) + f);
		}
	}

	return out;
}

float Linalg::sum(Matrix m)
{
	float sum = 0;

	int rows = m.getRows();
	int cols = m.getCols();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			sum += m.get(i, j);
		}
	}

	return sum;
}

bool Linalg::checkEquality(Matrix m1, Matrix m2)
{
	if (m1.getRows() != m2.getRows() || m1.getCols() != m2.getCols())
	{
		cout << "For this functions both matrices must have the same dimensionality" << endl;
		return false;
	}
	return true;
}