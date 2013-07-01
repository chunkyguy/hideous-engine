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

	class TextureShader;
	class ImageViewFactory;
	
	class ColorShader;
	class GradientViewFactory;
	
	class TextShader;
	class TextFactory;
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
	he::Asset<he::ImageViewFactory> bg_factory_;
	he::Asset<he::ImageViewFactory> homescreen_factory_;
	he::Asset<he::ImageViewFactory> fishmotion_factory_;
	he::Asset<he::TextureShader> texture_shader_;

	he::Asset<he::ColorShader> clr_sh_;
	he::Asset<he::GradientViewFactory> gradient_view_factory_;
	
	he::Asset<he::ButtonListner<UITest> > btn_listener_;
	
	he::Asset<he::TextShader> txt_shader_;
	he::Asset<he::TextFactory> txt_factory_;
};


#endif /* defined(__HideousGameEngine__UITest__) */
