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
#include <he/Utils/Transform.h>
#include <he/UI/View.h>

namespace he{
	class Font;
	class Text;
	class TextView;
	class TextShader;
}

class AnimatedTextView : public he::View {
public:
	AnimatedTextView(const he::Transform &transform, he::TextShader *shader, he::Font *font,
					 const std::string &string, GLKVector4 color = GLKVector4Make(1.0f, 1.0f, 1.0f, 1.0f));
	virtual ~AnimatedTextView();
	virtual void Update(float dt);
	virtual void Render();
	virtual GLKVector2 GetSize() const;
	
private:
	void update_string();
	
	he::TextView *txt_vw_;
	he::Text *text_;
	std::string string_;
	float clock_;
	unsigned int length_;
	GLKVector4 color_;
};

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
//	he::TextViewFactory *factory_;
	he::Font *font_;
	he::View *view_;
	he::TextShader *shader_;
	he::GestureListener<RectTextTest> *gesture_listener_;
	
	AnimatedTextView *anim_txt_vw_;
};
#endif /* defined(__HideousGameEngine__RectTextTest__) */
