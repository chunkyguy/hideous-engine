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
#include "RunningSquare.h"

namespace he{
	class RectColorSh;
}

class RectColorTest : public ITest{
public:
	~RectColorTest();
	RectColorTest(double w, double h);
	void Update(double dt);
	void Render();
	
private:
	const int kTotal_squares = 300;
	
	void load_squares();
	void unload_squares();
	void handle_gestures();
	
	RunningSquare **squares_;
	he::RectColorSh *shader_;
};

#endif /* defined(__HideousGameEngine__RectColorTest__) */