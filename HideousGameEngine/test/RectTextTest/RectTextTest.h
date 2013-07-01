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
	class TextFactory;
	class TextShader;
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

	he::Text *text_small_;
	he::Text *text_caps_;
	he::Text *text_nums_;
	he::Text *text_sp_;
	he::TextFactory *factory_;
	he::TextShader *shader_;
	he::GestureListener<RectTextTest> *gesture_listener_;
};
#endif /* defined(__HideousGameEngine__RectTextTest__) */
