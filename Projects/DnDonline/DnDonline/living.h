#pragma once
#include "entity.h"

class living : public entity {
public:
	living(Uint8 teamNum);
	~living();
private:
	Uint8 team;
};