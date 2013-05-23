//
//  UITest.h
//  HideousGameEngine
//
//  Created by Sid on 26/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

// TODO: UISlider
#ifndef __HideousGameEngine__UITest__
#define __HideousGameEngine__UITest__
#include "TestTemplate.h"

#include <he/EventLoop/Gesture.h>

namespace he{
	class RenderObject;
	//	class AnimationChain;
	class RectColorSh;
	class VertexCol;
	class Font;
}
class Label;

class UITest : public ITest{
public:
	~UITest();
	UITest(double width, double height);
	void Update(double dt);
	void Render();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	
	he::Font *font_;
	Label *label_;
	he::RenderObject *render_object_;
	he::RectColorSh *shader_;
	he::VertexCol *vertex_data_;
	//	he::AnimationChain *scale_animation_;
	he::GestureListener<UITest> *gesture_listener_;
};


#endif /* defined(__HideousGameEngine__UITest__) */
