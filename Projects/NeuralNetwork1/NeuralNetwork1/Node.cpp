#include "Node.h"

//constructor
Node::Node(Network* n, int l) {
	parentNetwork = n;
	layerNum = l;

	for (int c = 0; c < parentNetwork->getLayerSize(layerNum-1); c++) {   //this minus 1 means the layer before it (regardless of what its actual position is)
		weights.push_back(0.0);
		previousChanges.push_back((float)rand() / (float)RAND_MAX);
	}
}
int Node::getValue() {
	return value;
}
void Node::updateValue() {
	float total = 0.0;

	for (int x = 0; x < weights.size(); x++) {
		total += parentNetwork->getNode(layerNum-1,x)->getValue() * weights.at(x);
	}

	value = total;
}