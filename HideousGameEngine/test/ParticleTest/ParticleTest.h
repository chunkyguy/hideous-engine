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
	class Texture;
	class ParticleEnv;
	class ParticleBatch;
	class ParticleSh;
}

class ParticleTest : public ITest{
public:
	~ParticleTest();
	ParticleTest(double w, double h);
	void Update(double dt);
	void Render();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	he::ParticleSh *shader_;
	he::Texture *texture_;
	he::ParticleEnv *environment_;
	he::ParticleBatch *particles_;
	he::GestureListener<ParticleTest> *gesture_listner_;
	
	
	void load(GLKVector2 at);
	void unload();
};

#endif /* defined(__HideousGameEngine__ParticleTest__) */
