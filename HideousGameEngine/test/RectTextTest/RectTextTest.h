//
//  RectTextTest.h
//  HideousGameEngine
//
//  Created by Sid on 13/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__RectTextTest__
#define __HideousGameEngine__RectTextTest__
#include "TestTemplate.h"

#include <he/EventLoop/Gesture.h>

namespace he{
	class Font;
	class Text;
}

class RectTextTest : public ITest{
public:
	~RectTextTest();
	RectTextTest(double width, double height);
	void Update(double dt);
	void Render();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	void load_text();
	void unload_text();

	he::Font *font_;
	he::Text *text_;
	he::GestureListener<RectTextTest> *gesture_listener_;
};
#endif /* defined(__HideousGameEngine__RectTextTest__) */
