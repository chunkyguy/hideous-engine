//
//  AnimationTest.h
//  HideousGameEngine
//
//  Created by Sid on 01/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__AnimationTest__
#define __HideousGameEngine__AnimationTest__

#include <he/Main/HideousGame.h>

#include <he/EventLoop/Gesture.h>

#include "AnimObj.h"

namespace he{
	class ColorShader;
}


class AnimationTest : public he::Game{
public:
	~AnimationTest();
	AnimationTest();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	virtual void init();
	virtual void update(float dt);
	virtual void render();

	const int kObjects_;
	
	void load();
	void unload();
	
	AnimObj **objects_;
	int active_object_;
	he::GestureListener<AnimationTest> *gesture_listner_;
	he::ColorShader *shader_;
};

#endif /* defined(__HideousGameEngine__AnimationTest__) */
