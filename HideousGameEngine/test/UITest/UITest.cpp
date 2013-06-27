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
//#include <he/UI/Label.h>

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
	btn_listener_.Move(new he::ButtonListner<UITest>(this, &UITest::ButtonHandler), false);
	he::Frame btn_frame(he::Transform_Create(GLKVector3Make(0, 0, 0)), mission_vw->GetFrame().GetSize());
	he::Button *btn = new he::Button(btn_frame, btn_listener_.Get(), 99);
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
	font.Move( new he::Font(he::ResourcePath() + "Silom.ttf", 48), false );
	txt_shader_.Move( new he::TextShader, false);
	
	//text view
	he::TextFactory txt_factory(font.Get(), txt_shader_.Get());
	he::Frame txt_frame(he::Transform_Create(GLKVector3Make(0.0, 0.0, 0.0)), GLKVector2Make(0, 0));
	he::Text *txt = new he::Text(txt_frame, &txt_factory, "hello");
	bg_vw->MoveSubview(txt);

	//gradient factory
	clr_sh_.Move(new he::ColorShader, false);
	clr_vertex_.Move(new he::ColorVertex({GLKVector2Make(0, 0), GLKVector4Make(1.0, 0.0, 0.0, 1.0)}, {GLKVector2Make(100, 100), GLKVector4Make(0.0, 1.0, 0.0, 1.0)}), false);

	//gradient view
	he::Frame gr_frame(he::Transform_Create(GLKVector3Make(0.0, 0.0, 0.0)));
	he::GradientView::Factory *gv_factory = new he::GradientView::Factory(clr_sh_.Get(), clr_vertex_.Get());
	he::GradientView *g_vw = new he::GradientView(gr_frame, gv_factory);
	bg_vw->MoveSubview(g_vw);
	
//	he::LabelFactory lbl_factory(font.Get());
//	he::Frame txt_frame(he::Transform(GLKVector3Make(0, 0, he::g_Screen->z_)));
//	std::string str("hello");
//	he::Label *lbl = new he::Label(txt_frame, &lbl_factory, str, GLKVector4Make(0.1, 1.0, 0.4, 1.0));
//	view_->AddSubview(lbl);
	
//	std::string btn_titles[] = {	"mission", "tutorial", "credits"	};
//	GLKVector3 pos = GLKVector3Make(0, 60, 0.0f);
//	he_Trace("\ni = %d\n",i);
//	std::string full_name(he::FlashFullName(btn_titles[i]));
//	const he::TextureAtlasRegion *region = atlas_.Get()->GetTextureAtlasRegion(full_name);
//	he::Transform trans(pos);
//	he_Trace("trans.pos = %@\n",trans.GetPosition());
//	he::Frame f(trans, region->sprite_size_);
//	he_Trace("f.rect = %@\n",f.GetRect());
//	he::Button *btn = new he::Button(btn_listener_.Get(), f, i);
//	he::ImageView *img_vw = new he::ImageView(&img_factory, full_name, f);
//	btn->AddSubview(img_vw);
//	view_->AddSubview(btn);
//	pos.y -= 60;
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
