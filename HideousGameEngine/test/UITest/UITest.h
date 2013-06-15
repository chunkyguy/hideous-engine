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
#include <he/Main/HideousGame.h>

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

class UITest : public he::Game{
public:
	~UITest();
	UITest(GLKVector3 cc);
	void ButtonHandler(he::ui::Button *sender);
	
private:
	void update(float dt);
	void render();

	he::ui::View *view_;
	he::Asset<he::Texture> texture_;
	he::Asset<he::TextureVertex> vertex_;
	he::Asset<he::TextureShader> shader_;
	he::Asset<he::TextureAtlas> atlas_;
	he::Asset<he::ui::ButtonListner<UITest> > btn_listener_;
};


#endif /* defined(__HideousGameEngine__UITest__) */
