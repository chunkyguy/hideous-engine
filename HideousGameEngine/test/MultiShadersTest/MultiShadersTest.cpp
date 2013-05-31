//
//  MultiShadersTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 19/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "MultiShadersTest.h"

#include <string>
#include <algorithm>

#include <he/ParticleSystem/Particle.h>
#include <he/ParticleSystem/ParticleEnv.h>
#include <he/Shaders/ParticleSh/ParticleSh.h>
#include <he/Texture/Texture.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Utils.h>
#include <he/Utils/ResourcePath.hpp>

namespace{
	double randf_epsilon(double d){
		return he::Randf() * d + std::numeric_limits<double>::epsilon();
	}
}

MultiShadersTest::~MultiShadersTest(){
	unload_objects();
	he::g_EventLoop->RemoveListener(gesture_listner_);
	delete gesture_listner_;
	
	he::GlobalsDestroy();
}

MultiShadersTest::MultiShadersTest(double w, double h) :
color_object_(nullptr),
factory_(nullptr),
gesture_listner_(nullptr),
load_indx_(),
text_object_(nullptr),
texture_object_(nullptr),
particle_shader_(nullptr),
particle_texture_(nullptr),
particles_(nullptr),
environment_(nullptr)
{
	//setup globals
	he::GlobalsInit(w, h);

	//debugger
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "MultiShadersTest Logging Enabled: " << loglevel << std::endl;

	//start things here
	for (int i = 0; i < kShaders; ++i) {
		load_indx_[i] = i;
	}
	srand(time(NULL));
	
	gesture_listner_ = new he::GestureListener<MultiShadersTest>(this, &MultiShadersTest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listner_);

	//waiting for input
}
void MultiShadersTest::Render(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if(factory_){
		for(int i = 0; i < kShaders; ++i){
			switch(load_indx_[i]){
				case 0: color_object_->Render(); break;
				case 1: 	texture_object_->Render(); break;
				case 2: text_object_->Render(); break;
				case 3:{
					if(particles_){
						particles_->Render();
					}
				}break;
			}
		}
	}
}


void MultiShadersTest::Update(double dt){
	if(particles_){
		particles_->Update(dt);
	}
}

void MultiShadersTest::load_objects(){
	if(factory_){
		unload_objects();
	}
	
	factory_ = new ObjectFactory;
	
	for(int i = 0; i < kShaders; ++i){
		switch(load_indx_[i]){
			case 0:
				FILE_LOG(logDEBUG) << "create Colored Obj";
				color_object_ = factory_->CreateColoredObject();
				break;
				
			case 1:
				FILE_LOG(logDEBUG) << "create Texture Obj";
				texture_object_ = factory_->CreateTexturedObject();
				break;
				
			case 2:
				FILE_LOG(logDEBUG) << "create Text Obj";
				text_object_ = factory_->CreateTextObject();
				break;
				
			case 3:{
				particle_shader_ = new he::ParticleSh;
				particle_texture_ = new he::Texture(he::ResourcePath() + "snow_particle.png");
				GLKVector2 box[2] = {GLKVector2Make(-3, -3), GLKVector2Make(3, 3)};
				double life_range[2] = {randf_epsilon(0.1), randf_epsilon(0.5)};
				double deathrate_range[2] = {randf_epsilon(0.01), randf_epsilon(0.08)};
				double birth_delay_range[2] = {randf_epsilon(0.1), randf_epsilon(0.3)};
				double birth_rate_range[2] = {randf_epsilon(0.01), randf_epsilon(0.3)};
				GLKVector2 vel_range[2] = {GLKVector2Make(randf_epsilon(-20.0), randf_epsilon(-20.0)), GLKVector2Make(randf_epsilon(20.0), randf_epsilon(20.0))};
				GLKVector4 color = GLKVector4Make(1, 1, 1, 0.8);
				//	GLKVector4 color = GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 0.5 + he::Randf()/2.0);
				
				int count  = 100;
				double point_size = 15.0;
				GLKVector2 pos = GLKVector2Make(0, 0);
				environment_ = new he::ParticleEnv(point_size, birth_delay_range, birth_rate_range,
												   box, color, deathrate_range, life_range,
												   vel_range);
				particles_ = new he::ParticleBatch(count, environment_, pos, particle_shader_, particle_texture_, color);
			}break;
		}
	}

	

	std::next_permutation(load_indx_, load_indx_+kShaders);
}

void MultiShadersTest::unload_objects(){
	delete color_object_; color_object_ = 0;
	delete texture_object_; texture_object_ = 0;
	delete text_object_; text_object_ = 0;
	delete factory_; factory_ = 0;
	delete particle_shader_; particle_shader_ = 0;
	delete particle_texture_; particle_texture_ = 0;
	delete environment_; environment_ = 0;
	delete particles_; particles_ = 0;
}

void MultiShadersTest::HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ == he::Gesture::kTap && gesture.state_ == he::Gesture::kEnd){
		load_objects();
	}
}
//EOF
