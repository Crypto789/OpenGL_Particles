#include "Particles.h"
#include <stdlib.h>
#include <math.h>
#include <SDL_stdinc.h>

Particles::Particles(): mX(0), mY(0)
{
	//mX = (2.0 * rand()) / RAND_MAX - 1;
	//mY = (2.0 * rand()) / RAND_MAX - 1;

	/*X_particle_speed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1);
	Y_particle_speed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1);*/
	init();
	
}
void Particles::init()
{
	mX = 0;
	mY = 0;
	mDirection = (2 * M_PI * rand()) / RAND_MAX;
	mSpeed = (0.0025 * rand()) / RAND_MAX;
	mSpeed *= mSpeed;
}
Particles::~Particles() 
{

}

void Particles::ParticlesUpdate(int interval)
{
	mDirection += interval * 0.00000050;
	//const double particle_speed = 0.001;
	//const double X_particle_speed = 0.01 * (((2.0 * rand()) / RAND_MAX) -1);
	//const double Y_particle_speed = (0.001 * rand() / RAND_MAX);
	//const double Y_particle_speed = 0.01 * (((2.0 * rand()) / RAND_MAX) - 1);

	/*mX += X_particle_speed;
	mY += Y_particle_speed;

	if (mX <= -1.0 || mX >= 1.0) 
	{
		X_particle_speed = -Y_particle_speed;
	}
	if (mY <= -1.0 || mY >= 1.0)
	{
		Y_particle_speed = -Y_particle_speed;
	}*/
	double xSpeed = mSpeed * cos(mDirection);
	double ySpeed = mSpeed * sin(mDirection);

	mX += xSpeed * interval;
	mY += ySpeed * interval;

	if (mX < -1 || mX > 1 || mY < -1 || mY > 1) 
	{
		init();
	}

	if (rand() < RAND_MAX / 100) 
	{
		init();
	}

}