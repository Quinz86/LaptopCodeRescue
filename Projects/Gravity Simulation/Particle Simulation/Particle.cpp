#include "Particle.h"
#include "TextureManager.h"
#include "Game.h"
#include "Math.h"

//force constant
#define K 0.5

//constructor
Particle::Particle(int x, int y, int m ) : Renderable(x,y,m/2,m/2,(m/2)/2,(m/2)/2){
	mass = m;

	posx = x;
	posy = y;
	velx = 0;//fRand(0.0, 0.2);
	vely = 0;//fRand(0.0, 0.2);


	
	sprite = TextureManager::myTextureGet("Neutral.png"); //neutral
	
}
Particle::~Particle() {

}




//inherited
void Particle::update() {
	double totalx = 0;
	double totaly = 0;
	for (int x = 0; x < particleListPointer->getParticleListPointer()->size(); x++) {
			Particle* o = particleListPointer->getParticleListPointer()->at(x);
		if(o != this){
			Force f = calculateForce(this, o);
			totalx += f.xComponent;
			totaly += f.yComponent;
		}
	}
	//totalx /= (particleListPointer->size() - 1); //these are forces
	//totaly /= (particleListPointer->size() - 1);

	velx += (totalx / mass); //f=ma,  a=f/m
	vely += (totaly / mass);

	posx += velx;
	posy += vely;

	//bouncing off walls
	if (posx > particleListPointer->getScreenWidth()) {
		posx = particleListPointer->getScreenWidth();
		velx *= -1;
		velx /= 1.2;
	}else if (posx < 0) {
		posx = 0;
		velx *= -1;
		velx /= 1.2;
	}
	if (posy > particleListPointer->getScreenHeight()) {
		posy = particleListPointer->getScreenHeight();
		vely *= -1;
		vely /= 1.2;
	}else if (posy < 0) {
		posy = 0;
		vely *= -1;
		vely /= 1.2;
	}


	move(posx, posy);
}
void Particle::render(SDL_Renderer* r) {
	SDL_RenderCopy(r, sprite, NULL, getRect());
}

//methods
double Particle::getMass() {
	return mass;
}
void Particle::addMass(double am) {
	mass += am;
}
double Particle::getX() {
	return posx;
}
double Particle::getY() {
	return posy;
}

//static
Game* Particle::particleListPointer = nullptr;
double Particle::fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}
Force Particle::calculateForce(Particle* me, Particle* other) {
	//return 0; //COMBINE THESE INTO ONE FUNCTION THAT RETURNS A {,} STRUCT FOR FORCE X AND FORCE Y
	//NEEDS TRIG
	double deltaX = other->getX() - me->getX();
	double deltaY = other->getY() - me->getY();
	double dis = sqrt((deltaX*deltaX) + (deltaY*deltaY));
	double theta = atan2(deltaY , deltaX);

	double totalForce = (K*me->getMass()*other->getMass()) / (dis*dis);


	return {cos(theta)*totalForce,sin(theta)*totalForce};
}
double Particle::calculateDistance(Particle* me, Particle* other) {
	double deltaX = other->getX() - me->getX();
	double deltaY = other->getY() - me->getY();
	double dis = sqrt((deltaX*deltaX) + (deltaY*deltaY));
	return dis;
}
void Particle::setup(Game* pl) {
	particleListPointer = pl;
}