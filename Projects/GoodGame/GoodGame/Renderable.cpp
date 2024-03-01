#include "Renderable.h"


//statics
bool Renderable::compHeights(Renderable * r1, Renderable * r2){
	return (r1->getFootPos() > r2->getFootPos());
}




//constructors
Renderable::Renderable() {
	
}
Renderable::~Renderable() {

}




