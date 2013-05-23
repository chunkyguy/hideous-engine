//
//  GestureTest.h
//  HideousGameEngine
//
//  Created by Sid on 25/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__GestureTest__
#define __HideousGameEngine__GestureTest__

#include "TestTemplate.h"

#include <he/EventLoop/Gesture.h>

#include "GObj.h"

class GestureTest : public ITest{
public:
	GestureTest(double width, double height);
	~GestureTest();
	void Update(double dt);
	void Render();
	void HandleGesture(const he::Gesture &gesture);
	
private:

	
	GObj obj_;
	he::GestureListener<GestureTest> *gesture_listner_;
};

#endif /* defined(__HideousGameEngine__GestureTest__) */
