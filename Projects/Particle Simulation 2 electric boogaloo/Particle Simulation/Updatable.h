#pragma once

class Updatable {
public:
	Updatable();
	~Updatable();

	virtual void update() = 0;
private:
};