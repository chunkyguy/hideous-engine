//
//  AnimationTest.h
//  HideousGameEngine
//
//  Created by Sid on 01/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__AnimationTest__
#define __HideousGameEngine__AnimationTest__

#include "TestTemplate.h"

#include <he/EventLoop/Gesture.h>

#include "AnimObj.h"

namespace he{
	class RectColorSh;
}


class AnimationTest : public ITest{
public:
	~AnimationTest();
	AnimationTest(double width, double height);
	void Update(double dt);
	void Render();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	const int kObjects_;
	
	void load();
	void unload();
	
	AnimObj **objects_;
	int active_object_;
	he::GestureListener<AnimationTest> *gesture_listner_;
	he::RectColorSh *shader_;
};

#endif /* defined(__HideousGameEngine__AnimationTest__) */
