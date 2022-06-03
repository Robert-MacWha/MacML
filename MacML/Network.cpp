#include "Network.h"

using namespace std;

Network::Network(int inputSize, int hiddenSize, int outputSize, float learningRate)
{
	Network::inputSize = inputSize;
	Network::hiddenSize = hiddenSize;
	Network::outputSize = outputSize;
	Network::learningRate = learningRate;

	Network::hiddenWeights = Matrix(hiddenSize, inputSize);
	Network::outputWeights = Matrix(outputSize, hiddenSize);

	Network::hiddenWeights.randomize(-1, 1);
	Network::outputWeights.randomize(-1, 1);
}

Matrix Network::predict(Matrix inputs)
{
	// Forward propogation through the network.  The number of inputs in this array must match the network's input size
	if (inputs.getRows() != Network::inputSize || inputs.getCols() != 1)
	{
		cout << "ERROR: Input shape invalid.  Input matrix must be of shape [inputSize X 1]" << endl;
		return Matrix();
	}

	Matrix hiddenInputs = Linalg::dot(Network::hiddenWeights, inputs);
	Matrix hiddenOutputs = Linalg::apply(hiddenInputs, &Network::sigmoid);

	Matrix finalInputs = Linalg::dot(Network::outputWeights, hiddenOutputs);
	Matrix finalOutputs = Linalg::apply(finalInputs, &Network::sigmoid);

	return finalOutputs;
}

float Network::trainOnBatch(Matrix inputSamples, Matrix outputSamples)
{
	// Train the network on a batch of samples
	if (inputSamples.getRows() != Network::inputSize)
	{
		cout << "ERROR: Input shape invalid.  Input matrix must be of shape [inputSize X 1]" << endl;
		return 0;
	}

	if (outputSamples.getRows() != Network::outputSize)
	{
		cout << "ERROR: Output shape invalid.  Output matrix must be of shape [outputSize X 1]" << endl;
		return 0;
	}

	if (inputSamples.getCols() != outputSamples.getCols())
	{
		cout << "ERROR: Number of input and output sample columns must be equal" << endl;
		return 0;
	}

	float errorSum = 0;
	for (int i = 0; i < inputSamples.getCols(); i++)
	{
		float* inputRow = inputSamples.getRow(i);
		float* outputRow = inputSamples.getRow(i);

		Matrix inputMatrix = Matrix::makeRow(Network::inputSize, inputRow);
		Matrix outputMatrix = Matrix::makeRow(Network::outputSize, outputRow);

		errorSum += Network::trainOnSample(inputMatrix, outputMatrix);
	}

	return errorSum / inputSamples.getCols();
}


float Network::trainOnSample(Matrix inputSample, Matrix outputTarget)
{
	// Train the network on a single sample
	if (inputSample.getRows() != Network::inputSize || inputSample.getCols() != 1)
	{
		cout << "ERROR: Input shape invalid.  Input matrix must be of shape [inputSize X 1]" << endl;
		return 0;
	}

	if (outputTarget.getRows() != Network::outputSize || outputTarget.getCols() != 1)
	{
		cout << "ERROR: Output shape invalid.  Output matrix must be of shape [outputSize X 1]" << endl;
		return 0;
	}
	
	// forward propogation
	Matrix hiddenInputs = Linalg::dot(Network::hiddenWeights, inputSample);
	Matrix hiddenOutputs = Linalg::apply(hiddenInputs, &Network::sigmoid);

	Matrix finalInputs = Linalg::dot(Network::outputWeights, hiddenOutputs);
	Matrix finalOutputs = Linalg::apply(finalInputs, &Network::sigmoid);

	// errors
	Matrix outputErrors = Linalg::sub(outputTarget, finalOutputs);
	Matrix hiddenErrors = Linalg::dot(Network::outputWeights.transposed(), outputErrors);

	cout << outputErrors.getRows() << ", " << outputErrors.getCols() << endl;

	// back propogation
	Network::outputWeights = Linalg::add(
		Network::outputWeights,
		Linalg::scale(
			Linalg::dot(
				Linalg::multiply(
					outputErrors,
					Linalg::apply(finalOutputs, &Network::sigmoidPrime)
				),
				hiddenOutputs.transposed()
			),
			Network::learningRate
		)
	);

	Network::hiddenWeights = Linalg::add(
		Network::hiddenWeights,
		Linalg::scale(
			Linalg::dot(
				Linalg::multiply(
					hiddenErrors,
					Linalg::apply(hiddenOutputs, &Network::sigmoidPrime)
				),
				inputSample.transposed()
			),
			Network::learningRate
		)
	);

	return pow(Linalg::sum(outputErrors) / outputErrors.getRows(), 2);
}

float Network::sigmoid(float x)
{
	// Approximation of sigmoid, not entirely accurate but close enough
	return (x / (1 + abs(x)));
}


float Network::sigmoidPrime(float x)
{
	return x * (1 - x);
}