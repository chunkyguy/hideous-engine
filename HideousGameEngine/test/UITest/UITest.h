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
	class Texture;
	class Image;
	class TextureAtlas;

	class Sprite;
	
	class ColorShader;

	class Gradient;
	
	class TextShader;
	class TextViewFactory;
	
	class ParticleShader;
	class ParticleViewFactory;
	class ParticleEnv;
}

class UITest : public he::Game{
public:
	~UITest();
	UITest();
	void ButtonHandler(he::ButtonView *sender);
	
private:
	virtual void init();
	virtual void update(float dt);
	virtual void render();

	he::View *view_;
	he::Asset<he::TextureShader> texture_shader_;
	
	he::Asset<he::Texture>ship_tex_;
	he::Asset<he::Image> ship_img_;
	
	he::Asset<he::TextureAtlas> home_screen_atlas_;

	he::Asset<he::Image> mission_img_;
	he::Asset<he::Image> tutorial_img_;

	he::Asset<he::TextureAtlas> fish_atlas_;

	he::Asset<he::Sprite> fish_sprite_;
	
	he::Asset<he::ColorShader> clr_sh_;
	
	he::Asset<he::ButtonListener<UITest> > btn_listener_;
	
	he::Asset<he::TextShader> txt_shader_;
	he::Asset<he::TextViewFactory> txt_factory_;
	
	he::Asset<he::Gradient> gr_mono_;
	he::Asset<he::Gradient> gr_dual_;
	he::Asset<he::Gradient> gr_quad_;
	
	he::Asset<he::ParticleShader> par_shader_;
	he::Asset<he::ParticleViewFactory> par_factory_;
	he::Asset<he::ParticleEnv> par_env_;
};


#endif /* defined(__HideousGameEngine__UITest__) */
