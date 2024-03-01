#include "Node.h"
#include "Path.h"

//constructor
Node::Node(int nx, int ny) {
	x = nx;
	y = ny;
	connections = std::vector<Path*>();
}