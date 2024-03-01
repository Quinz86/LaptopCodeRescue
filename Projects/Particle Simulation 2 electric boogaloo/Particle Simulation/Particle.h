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
	Particle(int x, int y, int m, int q);
	~Particle();

	void update();
	void render(SDL_Renderer* r);

	double getCharge();
	double getX();
	double getY();

	static void setup(Game* pl);
private:
	int mass;
	int charge;

	double velx;
	double vely;
	double posx;
	double posy;

	SDL_Texture* sprite;

	static double fRand(double fMin, double fMax);
	static Force calculateForce(Particle* me, Particle* other);
	static Game* particleListPointer;
};