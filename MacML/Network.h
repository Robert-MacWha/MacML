#pragma once

#include <iostream>
#include "Backend/Linalg.h"

class Network
{
private:
	int inputSize;
	int hiddenSize;
	int outputSize;
	float learningRate;

	Matrix hiddenWeights;
	Matrix outputWeights;

	static float sigmoid(float x);
	static float sigmoidPrime(float x);

public:
	Network(int inputSize, int hiddenSize, int outputSize, float learningRate);	
	Matrix predict(Matrix inputs);
	float trainOnSample(Matrix inputSample, Matrix outputSample);
	float trainOnBatch(Matrix inputSamples, Matrix outputSamples);
};
