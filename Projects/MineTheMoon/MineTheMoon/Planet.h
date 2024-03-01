#pragma once
#include "Living.h"
#include <vector>
#include <string>

class Planet {
public:
	Planet(std::string loadFile);
private:
	std::vector<std::vector<change>> layers; //layer height 96, width (4?)
};

struct change {
	bool to; //type
	double at; //angle
};