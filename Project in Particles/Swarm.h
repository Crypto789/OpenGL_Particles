#include "Particles.h"
class Swarm
{	
	public:
	 const static int mPARTICLES = 1000;
	private:
		Particles* mParticles;
		int last_time;
	public:
		Swarm();
		virtual ~Swarm();
		void ParticlesUpdate(int elapsed);

		const Particles* const get_particles() { return mParticles; };
};

