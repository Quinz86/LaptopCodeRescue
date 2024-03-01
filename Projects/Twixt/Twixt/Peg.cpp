#include "Peg.h"
#include <math.h>


void Peg::setConnection(unsigned char other, bool onOff) {
	unsigned char d = pow(2,other);

	if (onOff) {
		connections = (connections | d);
	}else{
		d = 255 - d;    //255 is correct
		connections = (connections & d);
	}
	
}
bool Peg::getConnection(unsigned char other) {
	unsigned char d = pow(2, other);

	return ( (connections & d) > 0);
}