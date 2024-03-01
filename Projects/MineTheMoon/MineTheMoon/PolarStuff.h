#pragma once
#include <math.h>

struct PolarCoords {
	int r;
	double theta;
};

double deltaTheta(int r, int horizontal) {
	double theta = (2*M_PI) * (horizontal/2*M_PI*r);
	return theta;
}

double modTau(double theta) {
	return 0.0; //fix this
}