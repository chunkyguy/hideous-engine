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
	ParticleView::ParticleView(const Frame &frame, ParticleBatch *p_batch) :
	View(frame),
	particles_(p_batch)
	{	}

	
	void ParticleView::Update(float dt){
		View::Update(dt);
		
		particles_->Update(dt);
	}
	
	void ParticleView::Render(){
		particles_->SetMVP(Transform_GetMVP(&(GetFrame().GetTransform())));
		particles_->Render();
		
		View::Render();
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ParticleViewFactory
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ParticleViewFactory::ParticleViewFactory(ParticleShader *shader, Texture *texture_m) {
		shader_.Set(shader);
		texture_m_.Move(texture_m);
	}
	
	ParticleView *ParticleViewFactory::CreateParticleView(const Transform &transform, he::ParticleEnv *environment, int count){
		assert(!texture_m_.IsEmpty());
		assert(!shader_.IsEmpty());
		
		GLKVector3 pos = transform.position;
		particles_m_.Move(new ParticleBatch(count, environment, GLKVector2Make(pos.x, pos.y), shader_.Get(), texture_m_.Get(), environment->color_), true);
		
		GLKVector2 size = environment->box_[1] - environment->box_[0];
		he::Frame frame(transform, size);
		return new ParticleView(frame, particles_m_.Get());
	}
}
// EOF //