#include <stdio.h>
#include <stdlib.h>
#include "sigmoid.h"

double Exponentiel (double x)
{
	int inverse = 0;
	double n = 0;
	double dl = 1;
	int i = 1;
	if (x < 0)
	{
		inverse = 1;
		x = -x;
	}
	while (x >= 2)
	{
		x /=2;
		n++;
	}
	x /= 16;
	n += 4;
	double q = x;
	while (q > 1.0E-15)
	{
		dl += q;
		i++;
		q = q*x/i;
	}
	for (i = 1; i <= n; i++)
	{
		dl=dl*dl;
	}
	if (inverse)
		dl = 1/dl;
	return dl;
}

double sigmoid (double x)
{
	return 1.0/(1.0 + Exponentiel(-x));
}

double deriv_sigmoid (double x)
{
	return x*(1-x);
}
