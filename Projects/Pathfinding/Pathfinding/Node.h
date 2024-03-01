#pragma once
#include <vector>

class Path;

class Node {
public:
	Node(int nx, int ny);

	
private:
	int x, y;
	std::vector<Path*> connections;
};