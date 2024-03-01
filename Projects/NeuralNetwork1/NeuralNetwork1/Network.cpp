#include "Network.h"
#include <iostream>
#include <algorithm>

#define numI 32
#define numH 10
#define numO 30 //abcdefghijklmnopqrstuvwxyz ,.:
#define numL 2
//constuctor
Network::Network() {
	int nodesinlayer[numL] = { 10,30 };
	layers.resize(numL);

	for (int x = 0; x < layers.size(); x++) {
		for (int y = 0; y < nodesinlayer[x];y++) {
			layers.at(x).push_back(new Node(this,x+1));
		}
	}
}
int Network::getLayerSize(int num) {
	if (num == 0) {
		return 32;
	}
	return layers.at(num - 1).size(); //this minus 1 corrects the x+1 above, accounting for the fact that the input layer is not in the layers vector
}
Node* Network::getNode(int layer, int pos) {
	if (layer == 0) {
		return nullptr; //this is where you return the string values
	}
	return layers.at(layer - 1).at(pos);
}

void Network::trainWith(std::string data) {
	std::cout << "TRAINING WITH SENTENCE: \"" + data +"\"" << std::endl;
	readingString = data;
	for (int l = 0; l < readingString.size(); l++) { // l means letter, guess char on each letter
		guessNextChar();

	}

}
std::string Network::createData(float temperature) {
	readingString = "";




	return readingString;
}

///~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
char Network::guessNextChar() {
	for (int x = 0; 0 < layers.size(); x++) {
		for (int y = 0; y < layers.at(x).size(); y++) {
			layers.at(x).at(y)->updateValue();
		}
	}

	int currentBest = 0;
	float currentValue = 0.0;
	for (int x = 0; x < layers.at(-1).size(); x++) {
		if () {

		}
	}
}

bool compareValues(Node* n1, Node* n2) {
	return (n1->getValue() > n2->getValue());
}