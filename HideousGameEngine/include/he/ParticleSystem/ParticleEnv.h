//
//  ParticleEnv.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
 
// Update the environment to reflect changes in the particles at run time.

#ifndef ParticleSystem_ParticleEnv_h
#define ParticleSystem_ParticleEnv_h
#include <GLKit/GLKMath.h>
namespace he{
	
	class ParticleEnv{
	public:
		ParticleEnv(
					double birth_delay[2],
					double birth_rate[2],
					GLKVector2 box[2],
					GLKVector4 color,
					double death_rate[2],
					double life_span[2],
					GLKVector2 velocity[2]
					);
		
		double birth_delay_[2];
		double birth_rate_[2];
		GLKVector2 box_[2];
		GLKVector4 color_;
		double death_rate_[2];
		double life_span_[2];
		GLKVector2 velocity_[2];
	};
}
#endif
