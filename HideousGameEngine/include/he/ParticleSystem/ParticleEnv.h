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
#include <he/Utils/GLKMath_Additions.h>
namespace he{
	
	class ParticleEnv{
	public:
		ParticleEnv(
					float point_size,
					float birth_delay[2],
					float birth_rate[2],
					GLKVector2 box[2],
					GLKVector4 color,
					float death_rate[2],
					float life_span[2],
					GLKVector2 velocity[2]
					);
		
		float point_size_;				// the size of each particle
		float birth_delay_[2];			//	wait time before can reborn
		float birth_rate_[2];			//  if <= 0.0; you live only once.
		GLKVector2 box_[2];				//	position in space-time, relative to some core box
		GLKVector4 color_;				//	color of the particles.
		float death_rate_[2];			//	rate of dying. Greater means dying quick.
		float life_span_[2];				//	total life time available, decrease at each tick by factor of death_rate
		GLKVector2 velocity_[2];			//	velocity at which spreading out of the core box
	};
}
#endif
