#include <stdio.h>
#include <stdlib.h>
#include "sigmoid.h"
#include "neuron.h"

double output(struct Neuron N)
{
	double forsig = (N.weight[0]*N.input[0] + N.weight[1]*N.input[1]+ N.biasWeight);
	double out = sigmoid(forsig);
	return out;
}

double randfrom(double min, double max)
{
	double range = (max - min);
	double div = RAND_MAX / range;
	return min + (rand() / div);
}

struct Neuron randomizeWeights(struct Neuron N)
{
	N.weight[0] = randfrom(0.0,1.0);
	N.weight[1] = randfrom(0.0,1.0);
	N.biasWeight = randfrom(0.0,1.0);
	return N;
}

struct Neuron adjustWeights(struct Neuron N)
{
	N.weight[0] += N.error * N.input[0];
	N.weight[1] += N.error * N.input[1];
	N.biasWeight += N.error;
	return N;
}

