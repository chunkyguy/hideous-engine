//
//  ParticleTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 09/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "ParticleTest.h"

#include <he/ParticleSystem/Particle.h>
#include <he/ParticleSystem/ParticleEnv.h>
#include <he/Shaders/ParticleSh/ParticleSh.h>
#include <he/Texture/Texture.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Utils.h>

namespace{
	double randf_epsilon(double d){
		return he::Randf() * d + std::numeric_limits<double>::epsilon();
	}
}

ParticleTest::~ParticleTest(){
	delete texture_; texture_ = 0;
	delete shader_; shader_ = 0;

	if(particles_){
		unload();
	}
	
	he::g_EventLoop->RemoveListener(gesture_listner_);
	delete gesture_listner_;
	
	he::GlobalsDestroy();
}

ParticleTest::ParticleTest(double w, double h) :
shader_(new he::ParticleSh),
texture_(new he::Texture(he::ResourcePath() + "snow_particle.png")),
environment_(nullptr),
particles_(nullptr),
gesture_listner_(nullptr)
{
	//globals
	he::GlobalsInit(w, h);

	//debugger
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "Logging Enabled: " << loglevel << std::endl;
	FILE_LOG(logDEBUG) <<"{" <<w << "," << h << "}";
	
	//random
	srand(time(NULL));
	
	gesture_listner_ = new he::GestureListener<ParticleTest>(this, &ParticleTest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listner_);
	
	//start things here
}

void ParticleTest::Update(double dt){
	if(particles_){
		particles_->Update(dt);
	}
}
void ParticleTest::Render(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if(particles_){
		particles_->Render();
	}
}

void ParticleTest::HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ == he::Gesture::kTap && gesture.state_ == he::Gesture::kEnd){
		if(particles_){
			unload();
		}
		load(gesture.GetHitPoint());
	}
}

void ParticleTest::unload(){
	delete environment_; environment_ = nullptr;
	delete particles_; particles_ = nullptr;
}
void ParticleTest::load(GLKVector2 pos){
	
	GLKVector2 box[2] = {GLKVector2Make(-3, -3), GLKVector2Make(3, 3)};
	double life_range[2] = {randf_epsilon(0.1), randf_epsilon(0.5)};
	double deathrate_range[2] = {randf_epsilon(0.01), randf_epsilon(0.08)};
	double birth_delay_range[2] = {randf_epsilon(0.1), randf_epsilon(0.3)};
	double birth_rate_range[2] = {randf_epsilon(0.01), randf_epsilon(0.3)};
	GLKVector2 vel_range[2] = {GLKVector2Make(randf_epsilon(-20.0), randf_epsilon(-20.0)), GLKVector2Make(randf_epsilon(20.0), randf_epsilon(20.0))};
	GLKVector4 color = GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 0.5 + he::Randf()/2.0);
	
	//	<< "box: {" << box[0].x << "," << box[0].y << "}  | {" << box[1].x << "," << box[1].y << "}" << std::endl
	//	<< "life: "<< life_range[0] << " | " << life_range[1] << std::endl
	//	<< "death_rate: " << deathrate_range[0] << " | " << deathrate_range[1] << std::endl
	//	<< "birth_delay: " << birth_delay_range[0] << " | " << birth_delay_range[1] << std::endl
	//	<< "birth_rate: " << birth_rate_range[0] << " | " << birth_rate_range[1] << std::endl
	//	<< "vel: {" << vel_range[0].x << "," << vel_range[0].y << "}  | {" << vel_range[1].x << "," << vel_range[1].y << "}" << std::endl
	//	<< "color: {" << color.r << "," << color.g << "," << color.b << "," << color.a << "}" << std::endl;

	//	FILE_LOG(logDEBUG) << "Particles: " << count_ << std::endl;

	int count  = 2500;
	double point_size = 15.0;
	environment_ = new he::ParticleEnv(point_size, birth_delay_range, birth_rate_range,
									   box, color, deathrate_range, life_range,
									   vel_range);
	particles_ = new he::ParticleBatch(count, environment_, pos, shader_, texture_, color);
}
///EOF

