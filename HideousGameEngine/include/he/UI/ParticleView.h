//
//  ParticleView.h
//  HideousGameEngine
//
//  Created by Sid on 10/07/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_ParticleView_h
#define HideousGameEngine_ParticleView_h
#include <he/UI/View.h>

#include <he/Utils/Frame.h>
#include <he/Utils/Asset.h>
#include <he/Utils/Screen.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Texture/Texture.h>
#include <he/ParticleSystem/Particle.h>

namespace he {
	
	class Texture;
	class ParticleEnv;
	class ParticleShader;

	class ParticleView : public View {
	public:
		ParticleView(const Frame &frame, ParticleBatch *particles);
		
		virtual void Update(float dt);
		virtual void Render();
		
	private:
		ParticleBatch *particles_;
	};
	
	class ParticleViewFactory {
	public:
		ParticleViewFactory(ParticleShader *shader, Texture *texture_m);
		ParticleView *CreateParticleView(const Transform &trans, he::ParticleEnv *environment, int count);
		
	private:
		Asset<ParticleShader> shader_;
		Asset<Texture> texture_m_;
		Asset<ParticleBatch> particles_m_;
	};
}

#endif
