#pragma once
#include <vector>
#include "Network.h"

class Node {
public:
	Node(Network* n, int l);
	int getValue();
	void updateValue();
private:
	std::vector<float> weights;
	std::vector<float> previousChanges;

	Network* parentNetwork;
	int layerNum;
	float value;
};