//
//  ParticleView.cpp
//  HideousGameEngine
//
//  Created by Sid on 11/07/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/ParticleView.h>

#include <he/ParticleSystem/ParticleEnv.h>
#include <he/ParticleSystem/Particle.h>
#include <he/Shaders/ParticleShader.h>

namespace he{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ParticleView
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ParticleView::ParticleView(const Frame &frame, const int count, ParticleEnv *environment, ParticleShader *shader, Texture *texture) :
	View(frame)
	{
		GLKVector3 pos = frame.GetTransform().position;
		particles_ = new ParticleBatch(count, environment, GLKVector2Make(pos.x, pos.y), shader, texture, environment->color_);
	}

	ParticleView::~ParticleView(){
		delete particles_;
	}
	
	void ParticleView::update(float dt){
		particles_->Update(dt);
	}
	
	void ParticleView::render(){
		particles_->SetMVP(Transform_GetMVP(&(GetFrame().GetTransform())));
		particles_->Render();
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ParticleViewFactory
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ParticleViewFactory::ParticleViewFactory(ParticleShader *sh, Texture *texture_m){
		shader.Set(sh);
		texture.Move(texture_m);
	}
	
	ParticleView *ParticleViewFactory::CreateParticleView(const Transform &t, he::ParticleEnv *environment, int count){
		GLKVector2 size = environment->box_[1] - environment->box_[0];
		he::Frame frame(t, size);
		return new ParticleView(frame, count, environment, shader.Get(), texture.Get());
	}
}
// EOF //