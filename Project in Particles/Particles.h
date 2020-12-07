
struct Particles
{
		double mX;
		double mY;
		//double X_particle_speed;
		//double Y_particle_speed;
	private:
		double mSpeed;
		double mDirection;

		private:
			void init();
	public:
		Particles();
		virtual ~Particles();
		void ParticlesUpdate(int interval);
};

