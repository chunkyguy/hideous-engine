//
//  Particle.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

//	Keep living and dying.

#ifndef ParticleSystem_Particle_h
#define ParticleSystem_Particle_h

#include <he/Utils/GLKMath_Additions.h>

namespace he{
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Particle
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class ParticleEnv;

	class Particle{
	public:
		explicit Particle(ParticleEnv *environment);
		~Particle();
		void Update(float dt);
		void UpdateEnvironment(ParticleEnv *environment);
		
		float birth_delay_;			//	wait time before can reborn
		float birth_rate_;			//  if <= 0.0; you live only once.
		float death_rate_;			//	rate of dying. Greater means dying quick.
		int is_dead_;				//	flag set when life is over.
		float life_span_;			//	total life time available, decrease at each tick by factor of death_rate
		GLKVector2 position_;		//	position in space-time, relative to some core box
		GLKVector2 velocity_;		//	velocity at which spreading out of the core box
		ParticleEnv *environment_;
		
	private:
		void load_vars();
	};
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ParticleBatch
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class RenderObject;
	class VertexPar;
	class ParticleSh;
	class Texture;

	class ParticleBatch{
	public:
		ParticleBatch(int count, ParticleEnv *environment, const GLKVector2 &position, ParticleSh *shader, Texture *texture, const GLKVector4 &color);
		~ParticleBatch();
		void SetPosition(const GLKVector2 &position);
		void Update(float dt);
		void Render();
		
	private:
		he::RenderObject *render_object_;
		he::VertexPar *vertex_data_;		
		Particle **particles_;
		int count_;
	};
}
#endif