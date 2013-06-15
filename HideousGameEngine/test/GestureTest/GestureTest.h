//
//  GestureTest.h
//  HideousGameEngine
//
//  Created by Sid on 25/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__GestureTest__
#define __HideousGameEngine__GestureTest__

#include <he/Main/HideousGame.h>

#include <he/EventLoop/Gesture.h>

#include "GObj.h"

class GestureTest : public he::Game{
public:
	GestureTest(GLKVector3 cc);
	~GestureTest();
	void HandleGesture(const he::Gesture &gesture);
	
private:	
	void update(float dt);
	void render();

	GObj *obj_;
	he::GestureListener<GestureTest> *gesture_listner_;
};

#endif /* defined(__HideousGameEngine__GestureTest__) */
