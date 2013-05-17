//
//  ParticleTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 09/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "ParticleTest.h"

#include <he/EventLoop/Gesture.h>
#include <he/ParticleSystem/Particle.h>
#include <he/ParticleSystem/ParticleEnv.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/ParticleSh/ParticleSh.h>
#include <he/Texture/Texture.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Screen.h>
#include <he/Utils/Utils.h>
#include <he/Vertex/VertexPar.h>

namespace{
	double randf_epsilon(double d){
		return he::Randf() * d + std::numeric_limits<double>::epsilon();
	}
}

ParticleTest::~ParticleTest(){
	delete texture_; texture_ = 0;
	delete shader_; shader_ = 0;

	if(count_){
		unload();
	}
}

ParticleTest::ParticleTest(double w, double h) :
count_(0){
	FILE_LOG(logDEBUG) <<"{" <<w << "," << h << "}";
	//<<"{" << he::g_Screen.width/2 << "," << he::g_Screen.height << "}";
	
	//setup globals
	//debugger
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "Logging Enabled: " << loglevel << std::endl;
	//random
	srand(time(NULL));
	//screen constants
	he::g_Screen.width_ = w;
	he::g_Screen.height_ = h;
	he::g_Screen.projection_ = GLKMatrix4MakeOrtho(-w/2, w/2, -h/2, h/2, 0.1, 100.0);

	//start things here
	shader_ = new he::ParticleSh;
	texture_ = new he::Texture(he::ResourcePath() + "snow_particle.png");
}

void ParticleTest::Update(double dt){
	HandleGestures();
	for(int i = 0; i < count_; ++i){
		particles_[i]->Update(dt);
	}
}
void ParticleTest::Render(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for(int i = 0; i < count_; ++i){
		GLKVector2 pos = particles_[i]->position_;
		GLKMatrix4 tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
		GLKMatrix4 mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
		render_object_->mvp_ = mvpMat;
		render_object_->Render();
	}
	
}

void ParticleTest::HandleGestures(){
	if(he::g_Gesture.action_ == he::Gesture::kTap){
		if(count_){
			unload();
		}
		load(he::g_Gesture.GetHitPoint());
		he::g_Gesture.Reset();
	}
}

void ParticleTest::unload(){
	delete vertex_data_; vertex_data_ = 0;
	delete render_object_; render_object_ = 0;
	delete environment_; environment_ = 0;
	for(int i = 0; i < count_; ++i){
		delete particles_[i];
	}
	delete particles_; particles_ = 0;
	count_ = 0;
}
void ParticleTest::load(GLKVector2 pos){
	count_  = 10 + rand()%200;
	
	GLKVector2 box[2] = {GLKVector2Make(pos.x-3, pos.y-3), GLKVector2Make(pos.x+3, pos.y+3)};
	double life_range[2] = {randf_epsilon(0.1), randf_epsilon(0.5)};
	double deathrate_range[2] = {randf_epsilon(0.01), randf_epsilon(0.08)};
	double birth_delay_range[2] = {randf_epsilon(0.1), randf_epsilon(0.3)};
	double birth_rate_range[2] = {randf_epsilon(0.01), randf_epsilon(0.3)};
	GLKVector2 vel_range[2] = {GLKVector2Make(randf_epsilon(-20.0), randf_epsilon(-20.0)), GLKVector2Make(randf_epsilon(20.0), randf_epsilon(20.0))};
	GLKVector4 color = GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 0.5 + he::Randf()/2.0);

	FILE_LOG(logDEBUG) << "Particles: " << count_ << std::endl;
//	<< "box: {" << box[0].x << "," << box[0].y << "}  | {" << box[1].x << "," << box[1].y << "}" << std::endl
//	<< "life: "<< life_range[0] << " | " << life_range[1] << std::endl
//	<< "death_rate: " << deathrate_range[0] << " | " << deathrate_range[1] << std::endl
//	<< "birth_delay: " << birth_delay_range[0] << " | " << birth_delay_range[1] << std::endl
//	<< "birth_rate: " << birth_rate_range[0] << " | " << birth_rate_range[1] << std::endl
//	<< "vel: {" << vel_range[0].x << "," << vel_range[0].y << "}  | {" << vel_range[1].x << "," << vel_range[1].y << "}" << std::endl
//	<< "color: {" << color.r << "," << color.g << "," << color.b << "," << color.a << "}" << std::endl;
	
	vertex_data_ = new he::VertexPar(count_, 10 + he::Randf() * 10);
	render_object_ = new he::RenderObject(vertex_data_, shader_, texture_, he::g_Screen.projection_, color);
	environment_ = new he::ParticleEnv(birth_delay_range, birth_rate_range,
									   box, color,
									   deathrate_range, life_range,
									   vel_range);
	particles_ = new he::Particle *[count_];
	for(int i = 0; i < count_; ++i){
		particles_[i] = new he::Particle(environment_);
	}	
}
///EOF

