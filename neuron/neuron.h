#ifndef NEURON_H
#define NEURON_H

struct Neuron
{
	double input[2];
	double weight[2];
	double error;
	double biasWeight;
};

double output(struct Neuron N);
struct Neuron randomizeWeights(struct Neuron N);
struct Neuron adjustWeights(struct Neuron N);

#endif
