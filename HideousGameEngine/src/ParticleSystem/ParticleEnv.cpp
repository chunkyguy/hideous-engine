//
//  ParticleEnv.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/ParticleSystem/ParticleEnv.h>
#include <he/Utils/DebugLog.h>

namespace he{
	
	ParticleEnv::ParticleEnv(double point_size, double birth_delay[2],	double birth_rate[2],
							 GLKVector2 box[2], GLKVector4 color,
							 double death_rate[2],	 double life_span[2],
							 GLKVector2 velocity[2]) :
	point_size_(point_size)
	{
		for(int i = 0; i < 2; ++i){
			birth_delay_[i] = birth_delay[i];
			birth_rate_[i] = birth_rate[i];
			box_[i] = box[i];
			color_ = color;
			death_rate_[i] = death_rate[i];
			life_span_[i] = life_span[i];
			velocity_[i] = velocity[i];
		}
		
		FILE_LOG(logDEBUG) << "ParticleEnv: " << std::endl
		<< "birth_delay: " << birth_delay_[0] << " | " << birth_delay_[1] << std::endl
		<< "birth_rate: " << birth_rate_[0] << " | " << birth_rate_[1] << std::endl
		<< "box: {" << box_[0].x << "," << box_[0].y << "}  | {" << box_[1].x << "," << box_[1].y << "}" << std::endl
		<< "color: {" << color_.r << "," << color_.g << "," << color_.b << "," << color_.a << "}" << std::endl
		<< "death_rate: " << death_rate_[0] << " | " << death_rate_[1] << std::endl
		<< "life: " << life_span_[0] << " | " << life_span_[1] << std::endl
		<< "vel: {" << velocity_[0].x << "," << velocity_[0].y << "}  | {" << velocity_[1].x << "," << velocity_[1].y << "}" << std::endl;
	}
}
