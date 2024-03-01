#pragma once
#include <string>
#include <winsock2.h>
#define PORT 41352



class Board;

class MatchHandler {
public:
	MatchHandler(std::string fN, bool sP);

	void run(); // probably multithreadded???? nope

	void listen(SOCKET* s); // this should be multithreadded
private:
	std::string fileName;
	Board* b;
	bool singlePlayer;
	bool whitesTurn;

	
};