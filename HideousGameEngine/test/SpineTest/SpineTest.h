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

#include "test/spine/spine.h"
#include "test/spine/extension.h"

//#define DEBUG_DRAW

namespace he{
#if defined(DEBUG_DRAW)
	class RectColorSh;
#else
	class RectTextureSh;
#endif
	class TextureAtlas;
}

class SkeletonDrawable{
public:
	spine::Skeleton* skeleton_;
	spine::AnimationState* state_;
#if defined(DEBUG_DRAW)
	he::RectColorSh *shader_;
#else
	he::RectTextureSh *shader_;
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
	SpineTest(double width, double height);
	void Update(double dt);
	void Render();
	
private:
	//	spine::Atlas* atlas_;
	he::TextureAtlas *atlas_;
	spine::SkeletonData *skeletonData_;
	SkeletonDrawable* drawable_;
};
#endif /* defined(__HideousGameEngine__SpineTest__) */
