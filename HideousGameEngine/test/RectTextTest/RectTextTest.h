//
//  RectTextTest.h
//  HideousGameEngine
//
//  Created by Sid on 13/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__RectTextTest__
#define __HideousGameEngine__RectTextTest__
#include <he/Main/HideousGame.h>

#include <he/EventLoop/Gesture.h>

namespace he{
	class Font;
	class Text;
}

class RectTextTest : public he::Game{
public:
	~RectTextTest();
	RectTextTest();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	virtual void init();
	virtual void update(float dt);
	virtual void render();
	
	void load_text();
	void unload_text();

	he::Font *font_;
	he::Text *text_;
	he::GestureListener<RectTextTest> *gesture_listener_;
};
#endif /* defined(__HideousGameEngine__RectTextTest__) */
