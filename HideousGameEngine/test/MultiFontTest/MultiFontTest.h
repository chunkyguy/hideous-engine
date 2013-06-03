//
//  MultiFontTest.h
//  HideousGameEngine
//
//  Created by Sid on 24/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__MultiFontTest__
#define __HideousGameEngine__MultiFontTest__
#include "TestTemplate.h"

#include <he/EventLoop/Gesture.h>

namespace he{
	class Font;
	class Text;
};

class MultiFontTest : public ITest{
public:
	~MultiFontTest();
	MultiFontTest(float w, float h);
	void Update(float dt);
	void Render();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	he::Font *courier_;
	he::Font *simsun_;
	
	he::Text *whacky_;
	he::Text *labs_;
	
	he::GestureListener<MultiFontTest> *gesture_listner_;
	
	void load_text();
	void unload_text();
};
#endif /* defined(__HideousGameEngine__MultiFontTest__) */
