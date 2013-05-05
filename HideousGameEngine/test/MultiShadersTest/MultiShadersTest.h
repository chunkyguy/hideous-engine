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
#include "../Common/ObjectFactory.h"

class MultiShadersTest : public ITest{
public:
	~MultiShadersTest();
	MultiShadersTest(double w, double h);
	void Update(double dt);
	void Render();
	
private:
	ObjectFactory *factory_;
	int load_indx_[3];
	ColObj *color_object_;
	TextureObj *texture_object_;
	TextObj *text_object_;
	
	void load_objects();
	void unload_objects();
	void handle_gestures();
};

#endif /* defined(__HideousGameEngine__MultiShadersTest__) */
