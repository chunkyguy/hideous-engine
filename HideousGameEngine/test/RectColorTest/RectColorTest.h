//
//  RectColorTest.h
//  HideousGameEngine
//
//  Created by Sid on 10/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
//	Test template for all the test cases
//	Has all kind of factories set up

#ifndef __HideousGameEngine__RectColorTest__
#define __HideousGameEngine__RectColorTest__
#include <he/Main/HideousGame.h>

#include <he/EventLoop/Gesture.h>

#include "RunningSquare.h"

namespace he{
	class ColorShader;
}

class RectColorTest : public he::Game{
public:
	~RectColorTest();
	RectColorTest(GLKVector3 cc);
	void HandleGesture(const he::Gesture &gesture);
	
private:
	void update(float dt);
	void render();

	const int kTotal_squares = 3;
	
	void load_squares();
	void unload_squares();
	
	RunningSquare **squares_;
	he::ColorShader *shader_;
	he::GestureListener<RectColorTest> *gesture_listner_;
};

#endif /* defined(__HideousGameEngine__RectColorTest__) */
