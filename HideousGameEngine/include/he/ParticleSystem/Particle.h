//
//  Particle.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

//	Keep living and dying.

#ifndef ParticleSystem_Particle_h
#define ParticleSystem_Particle_h

#include <he/Utils/GLKMath_Additions.h>

namespace he{
	
	class ParticleEnv;
	
	class Particle{
	public:
		explicit Particle(ParticleEnv *environment);
		~Particle();
		void Update(double dt);
		void UpdateEnvironment(ParticleEnv *environment);
		
		double birth_delay_;
		double birth_rate_;
		double death_rate_;
		ParticleEnv *environment_;
		int is_dead_;
		double life_span_;
		GLKVector2 position_;
		GLKVector2 velocity_;
		
	private:
		void load_vars();
	};
}
#endif