#pragma once

#include <iostream>
#include "Matrix.h"

class Linalg
{
private:
	static bool checkEquality(Matrix m1, Matrix m2);
public:
	static Matrix scale(Matrix m, float f);
	static Matrix dot(Matrix m1, Matrix m2);
	static Matrix apply(Matrix m, float (*func)(float));
	static Matrix multiply(Matrix m1, Matrix m2);
	static Matrix add(Matrix m1, Matrix m2);
	static Matrix sub(Matrix m1, Matrix m2);
	static Matrix addScalar(Matrix m, float f);

	static float sum(Matrix m);
};


