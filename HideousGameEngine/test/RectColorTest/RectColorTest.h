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
#include "TestTemplate.h"

#include <he/EventLoop/Gesture.h>

#include "RunningSquare.h"

namespace he{
	class ColorShader;
}

class RectColorTest : public ITest{
public:
	~RectColorTest();
	RectColorTest(float w, float h);
	void Update(float dt);
	void Render();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	const int kTotal_squares = 3;
	
	void load_squares();
	void unload_squares();
	
	RunningSquare **squares_;
	he::ColorShader *shader_;
	he::GestureListener<RectColorTest> *gesture_listner_;
};

#endif /* defined(__HideousGameEngine__RectColorTest__) */
