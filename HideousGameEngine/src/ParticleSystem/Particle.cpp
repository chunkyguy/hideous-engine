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

#include <he/RenderObject/RenderObject.h>
#include <he/Texture/Texture.h>
#include <he/Shaders/ParticleShader.h>
#include <he/Utils/Screen.h>
#include <he/Vertex/ParticleVertex.h>

namespace {
	GLKVector2 GLKVector2_rand(GLKVector2 a, GLKVector2 b){
		return GLKVector2Make(he::Randf(a.x, b.x), he::Randf(a.y, b.y));
	}
}

namespace he{

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Particle
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		life_span_ = he::Randf(environment_->life_span_[0], environment_->life_span_[1]);
		death_rate_ = he::Randf(environment_->death_rate_[0], environment_->death_rate_[1]);
		birth_delay_ = he::Randf(environment_->birth_delay_[0],environment_->birth_delay_[1]);
		birth_rate_ = he::Randf(environment_->birth_rate_[0], environment_->birth_rate_[1]);
		velocity_ = GLKVector2_rand(environment_->velocity_[0], environment_->velocity_[1]);

		
//		FILE_LOG(logDEBUG) << "Particle::load" << std::endl
//		<< "position: {" << position.x << "," << position.y << "}" << std::endl
//		<< "life: "<< life_span << std::endl
//		<< "death_rate: " << death_rate << std::endl
//		<< "birth_delay: " << birth_delay << std::endl
//		<< "birth_rate: " << birth_rate << std::endl
//		<< "vel: {" << velocity.x << "," << velocity.y << "}" << std::endl;

	}
	void Particle::Update(float dt){
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

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ParticleBatch
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ParticleBatch::ParticleBatch(int count, ParticleEnv *environment, const GLKVector2 &position, ParticleShader *shader, Texture *texture, const GLKVector4 &color) :
	count_(count),
	particles_(new Particle* [count]),
	render_object_(nullptr),
	vertex_data_(nullptr)
	{
		for(int i = 0; i < count; ++i){
			particles_[i] = new Particle(environment);
		}
		vertex_data_ = new ParticleVertex(count, environment->point_size_);
		GLKMatrix4 tMat = GLKMatrix4MakeTranslation(position.x, position.y, -0.1);
		GLKMatrix4 mvp = GLKMatrix4Multiply(he::g_Screen->projection_, tMat);
		render_object_ = new RenderObject(vertex_data_, shader, texture, mvp, color);
	}
	
	ParticleBatch::~ParticleBatch(){
		for (int i = 0; i < count_; ++i) {
			delete particles_[i];
		}
		delete [] particles_;
		delete vertex_data_;
		delete render_object_;
	}

	void ParticleBatch::SetMVP(const GLKMatrix4 &mvp){
		render_object_->SetMVP(mvp);
	}

//	void ParticleBatch::SetPosition(const GLKVector2 &position){
//		GLKMatrix4 tMat = GLKMatrix4MakeTranslation(position.x, position.y, -0.1);
//		GLKMatrix4 mvp = GLKMatrix4Multiply(he::g_Screen->projection_, tMat);
//		render_object_->SetMVP(mvp);
//	}
	
	void ParticleBatch::Update(float dt){
		for( int i = 0; i < count_; ++i){
			particles_[i]->Update(dt);
			vertex_data_->SetData(i, particles_[i]->position_);
		}
	}

	void ParticleBatch::Render(){
		render_object_->Render();

//		for(int i = 0; i < count_; ++i){
//			GLKVector2 pos = particles_[i]->position_;
//			GLKMatrix4 tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
//			GLKMatrix4 mvpMat = GLKMatrix4Multiply(he::g_Screen->projection_, tMat);
//			render_object_->mvp_ = mvpMat;
//			render_object_->Render();
//		}
	}

}