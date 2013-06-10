//
//  SpineTest.h
//  HideousGameEngine
//
//  Created by Sid on 09/05/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__SpineTest__
#define __HideousGameEngine__SpineTest__
#include "TestTemplate.h"

#include <he/EventLoop/Gesture.h>

#include "test/spine/spine.h"
#include "test/spine/extension.h"

//#define DEBUG_DRAW

namespace he{
#if defined(DEBUG_DRAW)
	class ColorShader;
#else
	class TextureShader;
#endif
	class TextureAtlas;
	class Texture;
}

class SkeletonDrawable{
public:
	spine::Skeleton* skeleton_;
	spine::AnimationState* state_;
#if defined(DEBUG_DRAW)
	he::ColorShader *shader_;
#else
	he::TextureShader *shader_;
#endif
	float timeScale_;
	
	SkeletonDrawable (spine::SkeletonData* skeleton, spine::AnimationStateData* stateData = 0);
	~SkeletonDrawable ();
	
	void Update (float deltaTime);
	void Render();
	
//private:
//	GLKVector4 convert_to_tex_coords(GLKVector4 frame, GLKVector2 fullFrameSize);
};


class SpineTest : public ITest{
public:
	~SpineTest();
	SpineTest(float width, float height);
	void Update(float dt);
	void Render();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	void load(std::string animation_name);
	void unload();
	
	int animation_index_;
	he::TextureAtlas *atlas_;
	SkeletonDrawable* drawable_;
	spine::SkeletonData *skeletonData_;
	he::GestureListener<SpineTest> *gesture_listener_;
};
#endif /* defined(__HideousGameEngine__SpineTest__) */
