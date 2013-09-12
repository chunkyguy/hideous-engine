//
//  UITest.cpp
//  HideousGameEngine
//
//  Created by Sid on 26/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "UITest.h"

#include <string>

#include <he/Animation/SpriteAnimation.h>
#include <he/Font/Font.h>
#include <he/ParticleSystem/ParticleEnv.h>
#include <he/Shaders/ColorShader.h>
#include <he/Shaders/ParticleShader.h>
#include <he/Shaders/TextShader.h>
#include <he/Shaders/TextureShader.h>
#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Texture/TextureAtlasRegion.h>
#include <he/UI/GradientView.h>
#include <he/UI/ImageView.h>
#include <he/UI/ImageViewFactory.h>
#include <he/UI/ParticleView.h>
#include <he/UI/Sprite.h>
#include <he/UI/Text.h>
#include <he/Utils/DebugHelper.h>
#include <he/Utils/Frame.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Transform.h>
#include <he/Utils/Utils.h>
#include <he/Vertex/ColorVertex.h>
#include <he/Vertex/TextureVertex.h>

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
	view_ = new he::View(he::Transform_Create(GLKVector2Make(0.0f, 0.0f)));
	
	//Single texture
	ship_tex_.Move(new he::Texture(he::ResourcePath() + "ship_144.png"));
	ship_img_.Move(he::image::Create(texture_shader_.Get(), ship_tex_.Get()));

	//bg: image view - from texture
	he::Transform bg_vw_trans = he::Transform_Create(GLKVector3Make(0, 50, 0));
	he::ImageView *bg_vw = new he::ImageView(bg_vw_trans, ship_img_.Get());
	view_->MoveSubview(bg_vw);
	
	// homescreen atlas
	std::string home_atlas_data_path(he::ResourcePath() + "homescreen_ss.xml");
	std::string home_atlas_img_path(he::ResourcePath() + "homescreen_ss.png");
	home_screen_atlas_.Move(new he::TextureAtlas(home_atlas_data_path, home_atlas_img_path, he::TextureAtlas::kStarling));

	//mission: image view - from atlas
	std::string mission_vw_img_name = he::FlashFullName("mission");
	mission_img_.Move(he::image::Create(texture_shader_.Get(), home_screen_atlas_.Get(), mission_vw_img_name));
	he::Transform mission_vw_trans = he::Transform_Create(GLKVector3Make(100, 0, 0.0f));
	//GLKVector2 mission_vw_sz = home_screen_atlas_.Get()->GetTextureAtlasRegion(mission_vw_img_name).sprite_size_;
	he::ImageView *mission_vw = new he::ImageView(mission_vw_trans, mission_img_.Get());
	bg_vw->MoveSubview(mission_vw);

	//button
	btn_listener_.Move(new he::ButtonListener<UITest>(this, &UITest::ButtonHandler), false);
	he::ButtonView *btn = new he::ButtonView(he::CreateLocalFrame(mission_vw->GetSize()), btn_listener_.Get(), 99);
	mission_vw->MoveSubview(btn);

	//tutorial: image view - from atlas
	std::string tutorial_img_name = he::FlashFullName("tutorial");
	tutorial_img_.Move(he::image::Create(texture_shader_.Get(), home_screen_atlas_.Get(), tutorial_img_name));
	he::Transform tutorial_vw_trans = he::Transform_Create(GLKVector3Make(-50, 50, 0.0f));
	//	GLKVector2 tutorial_vw_sz = home_screen_atlas_.Get()->GetTextureAtlasRegion(tutorial_img_name).sprite_size_;
	he::ImageView *tutorial_vw = new he::ImageView(tutorial_vw_trans, tutorial_img_.Get());
	mission_vw->MoveSubview(tutorial_vw);

	//another factory
	std::string fish_atlas_data_path(he::ResourcePath() + "fishmotion.xml");
	std::string fish_atlas_img_path(he::ResourcePath() + "fishmotion.png");
	fish_atlas_.Move(new he::TextureAtlas(fish_atlas_data_path, fish_atlas_img_path, he::TextureAtlas::kStarling));

	//fish sprite
	std::string fish_sprite_name("fishmoving");
	fish_sprite_data_.Move(he::sprite::Create(fish_atlas_.Get(), fish_sprite_name));
	fish_sprite_.Move(he::sprite::Create(fish_sprite_data_.Get(), texture_shader_.Get(), fish_atlas_.Get(), -1, 0, 30.0f));

	he::Transform fish_trans = he::Transform_Create(GLKVector3Make(0, -100, 0.0f));
	//GLKVector2 fish_sprite_sz = fish_atlas_.Get()->GetTextureAtlasRegion(he::FlashFullName(fish_sprite_name)).sprite_size_;
	he::SpriteView *fish_sprite = new he::SpriteView(fish_trans, fish_sprite_.Get());
	view_->MoveSubview(fish_sprite);

	//text factory
	txt_shader_.Move( new he::TextShader, false);
	font_.Move(new he::Font(he::ResourcePath() + "Silom.ttf", 48));
	
	//text view
	text_.Move(new he::Text(txt_shader_.Get(), font_.Get(), "hello"));
	view_->MoveSubview(new he::TextView(he::Transform_Create(GLKVector3Make(0.0, 0.0, 0.0)), text_.Get()));

	//gradient shader
	clr_sh_.Move(new he::ColorShader, false);
	
	//gradient view - mono
	gr_mono_.Move(he::gradient::Create(GLKVector2Make(50.0f, 50.0f), clr_sh_.Get(), GLKVector4Make(1.0f, 0.0f, 0.4f, 0.8f)));
	//he::Frame gr_mono_frame(he::Transform_Create(GLKVector3Make(-100.0, 20.0, he::g_Screen->z_)), GLKVector2Make(30.0f, 30.0f));
	he::GradientView *gr_mono_vw = new he::GradientView(he::Transform_Create(GLKVector3Make(-100.0, 20.0, he::g_Screen->z_)), gr_mono_.Get());
	view_->MoveSubview(gr_mono_vw);
	
	//gradient view - dual
	gr_dual_.Move(he::gradient::Create(GLKVector2Make(50.0f, 50.0f), clr_sh_.Get(),GLKVector4Make(1.0f, 0.0f, 0.0f, 1.0f), GLKVector4Make(0.0f, 1.0f, 0.0f, 1.0f)));
	//he::Frame gr_dual_frame(he::Frame(he::Transform_Create(GLKVector3Make(0.0, 40.0, he::g_Screen->z_)), GLKVector2Make(30.0f, 30.0f)));
	he::GradientView *gr_dual_vw = new he::GradientView(he::Transform_Create(GLKVector3Make(0.0, 40.0, he::g_Screen->z_)), gr_dual_.Get());
	view_->MoveSubview(gr_dual_vw);

	//gradient view - quad
	gr_quad_.Move(he::gradient::Create(GLKVector2Make(50.0f, 50.0f), clr_sh_.Get(), GLKVector4Make(1.0f, 0.0f, 0.0f, 1.0f), GLKVector4Make(0.0f, 1.0f, 0.0f, 1.0f), GLKVector4Make(0.0f, 0.0f, 1.0f, 1.0f), GLKVector4Make(1.0f, 1.0f, 1.0f, 1.0f)));
	//he::Frame gr_quad_frame(he::Transform_Create(GLKVector3Make(100.0, 60.0, he::g_Screen->z_)), GLKVector2Make(30.0f, 30.0f));
	he::GradientView *gr_quad_vw = new he::GradientView(he::Transform_Create(GLKVector3Make(100.0, 60.0, he::g_Screen->z_)), gr_quad_.Get());
	view_->MoveSubview(gr_quad_vw);

	//particle factory
	par_shader_.Move(new he::ParticleShader, false);

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
	par_factory_.Move(new he::ParticleViewFactory(par_shader_.Get(), new he::Texture(he::ResourcePath() + "snow_particle.png")));

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

void UITest::ButtonHandler(he::ButtonView *sender){
	he_Trace("UITest::ButtonHandler: %d\n",sender->GetTag());
}
///EOF
