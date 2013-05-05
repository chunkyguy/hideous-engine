//
//  Particle.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//


#include <he/ParticleSystem/Particle.h>
#include <he/ParticleSystem/ParticleEnv.h>
#include <he/Utils/Utils.h>
#include <he/Utils/DebugLog.h>

namespace {
	double double_rand(double a, double b){
		return a + (b - a) * he::Randf();
	}
	GLKVector2 GLKVector2_rand(GLKVector2 a, GLKVector2 b){
		return GLKVector2Make(double_rand(a.x, b.x), double_rand(a.y, b.y));
	}
}

namespace he{
	
	Particle::Particle(ParticleEnv *environment) :
	environment_(environment)
	{
		load_vars();
	}
	
	Particle::~Particle(){
	}

	void Particle::UpdateEnvironment(ParticleEnv *environment){
		environment_ = environment;
	}
	
	void Particle::load_vars(){
		is_dead_ = 0;
		position_ = GLKVector2_rand(environment_->box_[0], environment_->box_[1]);
		life_span_ = double_rand(environment_->life_span_[0], environment_->life_span_[1]);
		death_rate_ = double_rand(environment_->death_rate_[0], environment_->death_rate_[1]);
		birth_delay_ = double_rand(environment_->birth_delay_[0],environment_->birth_delay_[1]);
		birth_rate_ = double_rand(environment_->birth_rate_[0], environment_->birth_rate_[1]);
		velocity_ = GLKVector2_rand(environment_->velocity_[0], environment_->velocity_[1]);

		
//		FILE_LOG(logDEBUG) << "Particle::load" << std::endl
//		<< "position: {" << position.x << "," << position.y << "}" << std::endl
//		<< "life: "<< life_span << std::endl
//		<< "death_rate: " << death_rate << std::endl
//		<< "birth_delay: " << birth_delay << std::endl
//		<< "birth_rate: " << birth_rate << std::endl
//		<< "vel: {" << velocity.x << "," << velocity.y << "}" << std::endl;

	}
	void Particle::Update(double dt){
		if(is_dead_ && birth_rate_ > 0.0){	//dead + rebirth possible
			birth_delay_ -= (dt * birth_rate_);
			is_dead_ = (birth_delay_ > 0.0) ? 1: 0;
			if(!is_dead_){
				load_vars();
			}
		}else if(!is_dead_){	// living normally
			life_span_ -= (dt * death_rate_);
			is_dead_ = (life_span_ < 0.0);
			if(!is_dead_){
				position_ = GLKVector2Add(position_, GLKVector2MultiplyScalar(velocity_, dt));
			}
		}
	}
	
}