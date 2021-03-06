//
//  MultiFontTest.h
//  HideousGameEngine
//
//  Created by Sid on 24/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__MultiFontTest__
#define __HideousGameEngine__MultiFontTest__
#include <he/Main/HideousGame.h>

#include <he/EventLoop/Gesture.h>

namespace he{
	class Font;
	class TextView;
	class Text;
	class TextShader;
};

class MultiFontTest : public he::Game{
public:
	~MultiFontTest();
	MultiFontTest();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	virtual void init();
	virtual void update(float dt);
	virtual void render();

	he::Font *courier_;
	he::Font *simsun_;

	he::Text *whacky_txt_;
	he::TextView *whacky_;
	
	he::Text *labs_txt_;
	he::TextView *labs_;

	he::TextShader *shader_;
	
	he::GestureListener<MultiFontTest> *gesture_listner_;
	
	void load_text();
	void unload_text();
};
#endif /* defined(__HideousGameEngine__MultiFontTest__) */
