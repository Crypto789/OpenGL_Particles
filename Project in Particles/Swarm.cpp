#include "Swarm.h"

Swarm::Swarm(): last_time(0)
{
	mParticles = new Particles[mPARTICLES];
}
Swarm::~Swarm() 
{
	delete[] mParticles;
}

void Swarm::ParticlesUpdate(int elapsed) 
{
    int interval = elapsed = elapsed - last_time;

    for (int i = 0; i < Swarm::mPARTICLES; i++)
    {
        mParticles[i].ParticlesUpdate(interval);
    }

    last_time = elapsed;
}