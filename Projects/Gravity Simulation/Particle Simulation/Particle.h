#pragma once
#include "Renderable.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Updatable.h"
#include <vector>
#include "Force.h"

class Game;

class Particle : public Renderable, public Updatable{
public:
	Particle(int x, int y, int m);
	~Particle();

	void update();
	void render(SDL_Renderer* r);

	double getMass();
	void addMass(double am);
	double getX();
	double getY();

	static void setup(Game* pl);
	static double calculateDistance(Particle* me, Particle* other);
private:
	int mass;

	double velx;
	double vely;
	double posx;
	double posy;

	SDL_Texture* sprite;

	static double fRand(double fMin, double fMax);
	static Force calculateForce(Particle* me, Particle* other);
	static Game* particleListPointer;
};