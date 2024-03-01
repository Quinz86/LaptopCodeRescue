#include "Timer.h"




Timer::Timer() {
	Timer(60);
}
Timer::Timer(double hertz) {
	setLength(hertz);
	resetTimer();
}
Timer::Timer(std::chrono::high_resolution_clock::duration len) {
	setLength(len);
	resetTimer();
}



void Timer::setLength(double hertz) {
	int t = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(std::chrono::seconds(1)).count();
	length = std::chrono::high_resolution_clock::duration((int)(t/hertz)); //rounding
}
void Timer::setLength(std::chrono::high_resolution_clock::duration len) {
	length = len;
}

void Timer::resetTimer() {
	start = std::chrono::high_resolution_clock::now();
}
bool Timer::isTimeElapsed() {
	return (std::chrono::high_resolution_clock::now() - start) >= length; 
}













