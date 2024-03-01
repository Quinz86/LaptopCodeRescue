#pragma once
#include <stdio.h>
#include <time.h>
#include <chrono>



class Timer {
public:
	Timer();
	Timer(double hertz);
	Timer(std::chrono::high_resolution_clock::duration len);

	void setLength(double hertz);
	void setLength(std::chrono::high_resolution_clock::duration len);
	void resetTimer();
	bool isTimeElapsed();

private:

	

	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::duration length;

};