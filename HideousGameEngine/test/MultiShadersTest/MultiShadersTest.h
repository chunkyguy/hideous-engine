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

class MultiShadersTest : public ITest{
public:
	~MultiShadersTest();
	MultiShadersTest(double w, double h);
	void Update(double dt);
	void Render();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	void load_objects();
	void unload_objects();

	ColObj *color_object_;
	ObjectFactory *factory_;
	he::GestureListener<MultiShadersTest> *gesture_listner_;
	int load_indx_[3];
	TextObj *text_object_;
	TextureObj *texture_object_;
};

#endif /* defined(__HideousGameEngine__MultiShadersTest__) */
