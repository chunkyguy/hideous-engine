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
	class Font;
	
	namespace ui{
		class View;
	}
}

class UITest : public he::Game{
public:
	~UITest();
	UITest();
	void ButtonHandler(he::Button *sender);
	
private:
	virtual void init();
	virtual void update(float dt);
	virtual void render();

	he::View *view_;
	he::Asset<he::Texture> texture_;
	he::Asset<he::TextureVertex> vertex_;
	he::Asset<he::TextureShader> shader_;
	he::Asset<he::TextureAtlas> atlas_;
	he::Asset<he::TextureAtlas> atlas2_;
	he::Asset<he::ButtonListner<UITest> > btn_listener_;
	he::Asset<he::Font> font;
};


#endif /* defined(__HideousGameEngine__UITest__) */
