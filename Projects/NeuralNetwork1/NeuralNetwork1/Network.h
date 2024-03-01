#pragma once
#include <vector>
#include "Node.h"
#include <string>

class Network {
public:
	Network();
	void trainWith(std::string data);
	std::string createData(float temperature);
	int getLayerSize(int num);
	Node* getNode(int layer, int pos);

private:
	std::vector<std::vector<Node*>> layers;

	std::string readingString;
	char guessNextChar();
};