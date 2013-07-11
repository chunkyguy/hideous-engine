//
//  UITest.cpp
//  HideousGameEngine
//
//  Created by Sid on 26/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "UITest.h"

#include <string>

#include <he/Font/Font.h>
#include <he/UI/Text.h>
#include <he/Shaders/TextShader.h>
#include <he/Shaders/TextureShader.h>
#include <he/Shaders/ColorShader.h>
#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Texture/TextureAtlasRegion.h>
#include <he/UI/ImageView.h>
#include <he/UI/Sprite.h>
#include <he/UI/GradientView.h>
#include <he/Utils/DebugHelper.h>
#include <he/Utils/Frame.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Utils.h>
#include <he/Vertex/TextureVertex.h>
#include <he/Vertex/ColorVertex.h>
#include <he/UI/ImageViewFactory.h>
#include <he/Shaders/ParticleShader.h>
#include <he/UI/ParticleView.h>
#include <he/ParticleSystem/ParticleEnv.h>

UITest::UITest() :
view_(nullptr)
{}

UITest::~UITest(){
	delete view_;
}

void UITest::init(){
	srand(time(NULL));

	// Create shader
	texture_shader_.Move(new he::TextureShader, false);
	
	//main view
	he::Frame frame(he::Transform_Create(GLKVector2Make(0, 0)));
	view_ = new he::View(frame);
	
	//bg_factory: Single texture based factory
	bg_factory_.Move(new he::ImageViewFactory(texture_shader_.Get(), he::ResourcePath() + "ship_144.png"));
	//bg: image view - from texture
	he::ImageView *bg_vw = bg_factory_.Get()->CreateImageView(he::Transform_Create(GLKVector3Make(0, 50, 0)));
	view_->MoveSubview(bg_vw);
	
	// homescreen factory
	std::string home_atlas_data_path(he::ResourcePath() + "homescreen_ss.xml");
	std::string home_atlas_img_path(he::ResourcePath() + "homescreen_ss.png");
	homescreen_factory_.Move(new he::ImageViewFactory(texture_shader_.Get(), home_atlas_data_path, home_atlas_img_path, he::TextureAtlas::kStarling ));

	//mission: image view - from atlas
	he::ImageView *mission_vw = homescreen_factory_.Get()->CreateImageView(he::Transform_Create(GLKVector3Make(100, 0, 0.0f)), he::FlashFullName("mission"));
	bg_vw->MoveSubview(mission_vw);

	//button
	btn_listener_.Move(new he::ButtonListener<UITest>(this, &UITest::ButtonHandler), false);
	he::Button *btn = new he::Button(CreateLocalFrame(mission_vw->GetFrame()), btn_listener_.Get(), 99);
	mission_vw->MoveSubview(btn);

	//tutorial: image view - from atlas
	he::ImageView *tutorial_vw = homescreen_factory_.Get()->CreateImageView(he::Transform_Create(GLKVector3Make(-50, 50, 0.0f)), he::FlashFullName("tutorial"));
	mission_vw->MoveSubview(tutorial_vw);

	//another factory
	std::string fish_atlas_data_path(he::ResourcePath() + "fishmotion.xml");
	std::string fish_atlas_img_path(he::ResourcePath() + "fishmotion.png");
	fishmotion_factory_.Move(new he::ImageViewFactory(texture_shader_.Get(), fish_atlas_data_path, fish_atlas_img_path, he::TextureAtlas::kStarling));

	//fish sprite
	he::Sprite *fish_sprite = fishmotion_factory_.Get()->CreateSprite(he::Transform_Create(GLKVector3Make(0, -100, 0.0f)), "fishmoving", -1, 0, 24.0f);
	view_->MoveSubview(fish_sprite);

	//text factory
	txt_shader_.Move( new he::TextShader, false);
	txt_factory_.Move(new he::TextFactory(txt_shader_.Get(), new he::Font(he::ResourcePath() + "Silom.ttf", 48)));
	
	//text view
	he::Text *txt = txt_factory_.Get()->CreateText(he::Transform_Create(GLKVector3Make(0.0, 0.0, 0.0)), "hello");
	view_->MoveSubview(txt);

	//gradient factory
	clr_sh_.Move(new he::ColorShader, false);
	gradient_view_factory_.Move(new he::GradientViewFactory(clr_sh_.Get()));

	//gradient view - mono
	he::GradientView *gr_mono_vw = gradient_view_factory_.Get()->CreateGradientView(he::Frame(he::Transform_Create(GLKVector3Make(-100.0, 20.0, he::g_Screen->z_)), GLKVector2Make(30.0f, 30.0f)), GLKVector4Make(1.0f, 0.0f, 0.0f, 1.0f));
	view_->MoveSubview(gr_mono_vw);
	
	//gradient view - dual
	he::GradientView *gr_dual_vw = gradient_view_factory_.Get()->CreateGradientView(he::Frame(he::Transform_Create(GLKVector3Make(0.0, 40.0, he::g_Screen->z_)), GLKVector2Make(30.0f, 30.0f)), GLKVector4Make(1.0f, 0.0f, 0.0f, 1.0f), GLKVector4Make(0.0f, 1.0f, 0.0f, 1.0f));
	view_->MoveSubview(gr_dual_vw);

	//gradient view - quad
	he::GradientView *gr_quad_vw = gradient_view_factory_.Get()->CreateGradientView(he::Frame(he::Transform_Create(GLKVector3Make(100.0, 60.0, he::g_Screen->z_)), GLKVector2Make(30.0f, 30.0f)), GLKVector4Make(1.0f, 0.0f, 0.0f, 1.0f), GLKVector4Make(0.0f, 1.0f, 0.0f, 1.0f), GLKVector4Make(0.0f, 0.0f, 1.0f, 1.0f), GLKVector4Make(1.0f, 1.0f, 1.0f, 1.0f));
	view_->MoveSubview(gr_quad_vw);

	//particle factory
	par_shader_.Move(new he::ParticleShader, false);
	par_factory_.Move(new he::ParticleViewFactory(par_shader_.Get()));

	//particle factory
	float point_size = 15.0;
	GLKVector2 box[2] = {GLKVector2Make(-30, -3), GLKVector2Make(30, 3)};
	float life_range[2] = {0.1, 0.5};
	float deathrate_range[2] = {0.05, 0.08};
	float birth_delay_range[2] = {0.1, 0.3};
	float birth_rate_range[2] = {0.01, 0.3};
	GLKVector2 vel_range[2] = {GLKVector2Make(-25.0, 0.0), GLKVector2Make(-5.0, 20.0)};
	GLKVector4 color = GLKVector4Make(0.0, 0.0, 1.0, 1.0);
	par_env_.Move(new he::ParticleEnv(point_size, birth_delay_range, birth_rate_range,
									  box, color, deathrate_range, life_range,
									  vel_range));
	int count  = 50;
	he::ParticleView *par_vw = par_factory_.Get()->CreateParticleView(he::Transform_Create(GLKVector3Make(30.0f, -5.0f, 0.0f)) ,par_env_.Get(), count);
	fish_sprite->MoveSubview(par_vw);
}

void UITest::update(float dt){
	view_->Update(dt);
}

void UITest::render(){
	view_->Render();
}

void UITest::ButtonHandler(he::Button *sender){
	he_Trace("UITest::ButtonHandler: %d\n",sender->GetTag());
}
///EOF
