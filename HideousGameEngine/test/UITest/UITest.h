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

#include <he/Utils/Asset.h>
#include <he/UI/Button.h>

namespace he{
	class Texture;
	class TextureShader;
	class TextureVertex;
	class TextureAtlas;
	
	namespace ui{
		class View;
	}
}

class UITest : public ITest{
public:
	~UITest();
	UITest(float width, float height);
	void Update(float dt);
	void Render();
	void ButtonHandler(he::ui::Button *sender);
	
private:
	he::ui::View *view_;
	he::Asset<he::Texture> texture_;
	he::Asset<he::TextureVertex> vertex_;
	he::Asset<he::TextureShader> shader_;
	he::Asset<he::TextureAtlas> atlas_;
	he::Asset<he::ui::ButtonListner<UITest> > btn_listener_;
};


#endif /* defined(__HideousGameEngine__UITest__) */
