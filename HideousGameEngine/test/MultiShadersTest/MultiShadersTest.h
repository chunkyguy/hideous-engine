//
//  MultiShadersTest.h
//  HideousGameEngine
//
//  Created by Sid on 19/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__MultiShadersTest__
#define __HideousGameEngine__MultiShadersTest__
#include "TestTemplate.h"

#include <he/EventLoop/Gesture.h>

#include "../Common/ObjectFactory.h"

namespace he {
	class Texture;
	class ParticleEnv;
	class ParticleBatch;
	class ParticleSh;
}

const int kShaders = 4;

class MultiShadersTest : public ITest{
public:
	~MultiShadersTest();
	MultiShadersTest(float w, float h);
	void Update(float dt);
	void Render();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	void load_objects();
	void unload_objects();

	ColObj *color_object_;
	ObjectFactory *factory_;
	he::GestureListener<MultiShadersTest> *gesture_listner_;
	int load_indx_[kShaders];
	TextObj *text_object_;
	TextureObj *texture_object_;
	
	//particles
	he::ParticleSh *particle_shader_;
	he::Texture *particle_texture_;
	he::ParticleEnv *environment_;
	he::ParticleBatch *particles_;
};

#endif /* defined(__HideousGameEngine__MultiShadersTest__) */
