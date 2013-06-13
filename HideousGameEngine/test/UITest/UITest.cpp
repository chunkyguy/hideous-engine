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

UITest::UITest(float w, float h)
{
	srand(time(NULL));
	//setup globals
	he::GlobalsInit(w, h);
	
	shader_.Load(new he::TextureShader, true);
	texture_.Load(new he::Texture(he::ResourcePath() + "ship_144.png"), true);
	vertex_.Load(new he::TextureVertex(texture_.Get()->GetSize()), true);
	std::string atlas_data_path(he::ResourcePath() + "homescreen_ss.xml");
	std::string atlas_img_path(he::ResourcePath() + "homescreen_ss.png");
	atlas_.Load(new he::TextureAtlas(atlas_data_path, atlas_img_path, he::TextureAtlas::kStarling), true);
	btn_listener_.Load(new he::ui::ButtonListner<UITest>(this, &UITest::ButtonHandler), true);
	
	he::ui::ImageViewFactory img_factory(shader_.Get(), atlas_.Get());
	he::Frame frame;
	view_ = new he::ui::View(frame);
	view_->AddSubview(new he::ui::ImageView(&img_factory, vertex_.Get(), texture_.Get()));
	std::string btn_titles[] = {	"mission", "tutorial", "credits"	};
	GLKVector2 pos = GLKVector2Make(0, 60);
	for(int i = 0; i < sizeof(btn_titles)/sizeof(btn_titles[0]); ++i){
		he_Trace("\ni = %d\n",i);
		std::string full_name(he::FlashFullName(btn_titles[i]));
		const he::TextureAtlasRegion *region = atlas_.Get()->GetTextureAtlasRegion(full_name);
		he::Transform trans(pos);
		he_Trace("trans.pos = %@\n",trans.GetPosition());
		he::Frame f(trans, region->sprite_size_);
		he_Trace("f.rect = %@\n",f.GetRect());
//		One way of creating imageviews
//		he::TextureVertex *vertex = new he::TextureVertex(region); //memory leak here!!
//		he::ui::ImageView *img_vw = new he::ui::ImageView(&img_factory,
//														  vertex,
//														  atlas_.Get()->GetTexture(), f);
		he::ui::ImageView *img_vw = new he::ui::ImageView(&img_factory, full_name, f);
		view_->AddSubview(img_vw);
		view_->AddSubview(new he::ui::Button(btn_listener_.Get(), f, i));
		pos.y -= 60;
	}
}

UITest::~UITest(){
	delete view_;
	he::GlobalsDestroy();
}


void UITest::Update(float dt){
	view_->Update(dt);
}

void UITest::Render(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	view_->Render();
}

void UITest::ButtonHandler(he::ui::Button *sender){
	he_Trace("btn hit: %d\n",sender->GetTag());
}
///EOF
