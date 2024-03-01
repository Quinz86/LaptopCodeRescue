#pragma once
#include <string>
#include <vector>

//this isnt bery useful right now
struct result {
	int clas;
	int aspect;
	int diff;
};


struct question {
	std::string ask;
	std::vector<result> results;
};

