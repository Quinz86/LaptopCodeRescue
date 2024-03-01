#pragma once
#include "Player.h"
#include <vector>

class Server {
public:
	Server();

private:
	std::vector<Player*> players;
};