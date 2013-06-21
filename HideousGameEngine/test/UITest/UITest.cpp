//
//  UITest.cpp
//  HideousGameEngine
//
//  Created by Sid on 26/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "UITest.h"

#include <string>

#include <he/Shaders/TextureShader.h>
#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Texture/TextureAtlasRegion.h>
#include <he/UI/ImageView.h>
#include <he/Utils/DebugHelper.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Utils.h>
#include <he/Utils/Frame.h>
#include <he/Vertex/TextureVertex.h>
#include <he/UI/Sprite.h>

UITest::UITest() :
view_(nullptr)
{}

UITest::~UITest(){
	delete view_;
}

void UITest::init(){
	srand(time(NULL));
	
	shader_.Load(new he::TextureShader, true);
	texture_.Load(new he::Texture(he::ResourcePath() + "ship_144.png"), true);
	vertex_.Load(new he::TextureVertex(texture_.Get()->GetSize()), true);
	std::string atlas_data_path(he::ResourcePath() + "homescreen_ss.xml");
	std::string atlas_img_path(he::ResourcePath() + "homescreen_ss.png");
	atlas_.Load(new he::TextureAtlas(atlas_data_path, atlas_img_path, he::TextureAtlas::kStarling), true);
	btn_listener_.Load(new he::ui::ButtonListner<UITest>(this, &UITest::ButtonHandler), true);
	
	he::ui::ImageViewFactory img_factory(shader_.Get(), atlas_.Get());
	
	//main view
	he::Frame frame;
	view_ = new he::ui::View(frame);
	
	//bg view
	he::Frame bg_vw_frame(he::Transform(GLKVector3Make(0, 50, 0)));
	he::ui::ImageView *bg_vw = new he::ui::ImageView(&img_factory, vertex_.Get(), texture_.Get(), bg_vw_frame);
	view_->AddSubview(bg_vw);
	
	//mission image view
	std::string mission_full_name(he::FlashFullName("mission"));
	const he::TextureAtlasRegion mission_region = atlas_.Get()->GetTextureAtlasRegion(mission_full_name);
	GLKVector3 mission_pos = GLKVector3Make(100, 0, 0.0f);
	he::Transform mission_trans(mission_pos);
	he_Trace("UITest:init: %@\n",mission_region.sprite_size_);
	he::Frame mission_frame(mission_trans, mission_region.sprite_size_);
	he::ui::ImageView *mission_img_vw = new he::ui::ImageView(&img_factory, mission_full_name, mission_frame);
	bg_vw->AddSubview(mission_img_vw);

	//button
	he::Frame btn_frame(he::Transform(GLKVector3Make(0, 0, 0)), mission_region.sprite_size_);
	he::ui::Button *btn = new he::ui::Button(btn_listener_.Get(), btn_frame, 99);
	mission_img_vw->AddSubview(btn);

	//tutorial image view
	std::string tutorial_full_name(he::FlashFullName("tutorial"));
	const he::TextureAtlasRegion tutorial_region = atlas_.Get()->GetTextureAtlasRegion(tutorial_full_name);
	GLKVector3 tutorial_pos = GLKVector3Make(-50, 50, 0.0f);
	he::Transform tutorial_trans(tutorial_pos);
	he::Frame tutorial_frame(tutorial_trans, tutorial_region.sprite_size_);
	he::ui::ImageView *tutorial_img_vw = new he::ui::ImageView(&img_factory, tutorial_full_name, tutorial_frame);
	mission_img_vw->AddSubview(tutorial_img_vw);

	//another factory
	std::string atlas_data_path2(he::ResourcePath() + "fishmotion.xml");
	std::string atlas_img_path2(he::ResourcePath() + "fishmotion.png");
	he::TextureAtlas *leakyatlas = new he::TextureAtlas(atlas_data_path2, atlas_img_path2, he::TextureAtlas::kStarling);
	
	he::ui::ImageViewFactory img_factory2(shader_.Get(), leakyatlas);

	//sprite
	std::string sprite_name("fishmoving");
	//const he::TextureAtlasRegion *sprite_region = leakyatlas->GetTextureAtlasRegion(mission_full_name);
	GLKVector3 sprite_pos = GLKVector3Make(0, -100, 0.0f);
	he::Transform sprite_trans(sprite_pos);
	he::Frame sprite_frame(sprite_trans, GLKVector2Make(0, 0));
	he::ui::Sprite *sprite = new he::ui::Sprite(&img_factory2, sprite_name, sprite_frame, -1, 24);
	view_->AddSubview(sprite);

	
//	std::string btn_titles[] = {	"mission", "tutorial", "credits"	};
//	GLKVector3 pos = GLKVector3Make(0, 60, 0.0f);
//	he_Trace("\ni = %d\n",i);
//	std::string full_name(he::FlashFullName(btn_titles[i]));
//	const he::TextureAtlasRegion *region = atlas_.Get()->GetTextureAtlasRegion(full_name);
//	he::Transform trans(pos);
//	he_Trace("trans.pos = %@\n",trans.GetPosition());
//	he::Frame f(trans, region->sprite_size_);
//	he_Trace("f.rect = %@\n",f.GetRect());
//	he::ui::Button *btn = new he::ui::Button(btn_listener_.Get(), f, i);
//	he::ui::ImageView *img_vw = new he::ui::ImageView(&img_factory, full_name, f);
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

void UITest::ButtonHandler(he::ui::Button *sender){
	he_Trace("UITest::ButtonHandler: %d\n",sender->GetTag());
}
///EOF
