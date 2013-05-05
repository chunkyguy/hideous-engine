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
#include "AnimObj.h"

class AnimationTest : public ITest{
public:
	~AnimationTest();
	AnimationTest(double width, double height);
	void Update(double dt);
	void Render();

private:
	void handle_gesture();
	void load();
	void unload();
	
	AnimObj *anim_obj_;
};

#endif /* defined(__HideousGameEngine__AnimationTest__) */
