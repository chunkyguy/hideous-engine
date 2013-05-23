//
//  ParticleTest.h
//  HideousGameEngine
//
//  Created by Sid on 09/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__ParticleTest__
#define __HideousGameEngine__ParticleTest__

#include "TestTemplate.h"

#include <he/EventLoop/Gesture.h>

namespace he{
	class RenderObject;
	class ParticleSh;
	class VertexPar;
	class Texture;
	class ParticleEnv;
	class Particle;
}

class ParticleTest : public ITest{
public:
	~ParticleTest();
	ParticleTest(double w, double h);
	void Update(double dt);
	void Render();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	he::RenderObject *render_object_;
	he::ParticleSh *shader_;
	he::Texture *texture_;
	he::VertexPar *vertex_data_;
	he::ParticleEnv *environment_;
	he::Particle ** particles_;
	he::GestureListener<ParticleTest> *gesture_listner_;
	int count_;
	
	
	void load(GLKVector2 at);
	void unload();
};

#endif /* defined(__HideousGameEngine__ParticleTest__) */
