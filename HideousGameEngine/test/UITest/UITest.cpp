//
//  UITest.cpp
//  HideousGameEngine
//
//  Created by Sid on 26/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "UITest.h"

#include <he/Shaders/TextureShader.h>
#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlas.h>
#include <he/UI/ImageView.h>
#include <he/Utils/DebugHelper.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Utils.h>
#include <he/Vertex/TextureVertex.h>

UITest::UITest(float w, float h)
{
	srand(time(NULL));
	//setup globals
	he::GlobalsInit(w, h);
	
	shader_.Load(new he::TextureShader, true);
	texture_.Load(new he::Texture(he::ResourcePath() + "ship_144.png"), true);
	vertex_.Load(new he::TextureVertex(texture_.Get()->GetSize()), true);

	he::ui::ImageViewFactory img_factory(shader_.Get());
	he::Transform transform;
	view_ = new he::ui::View(transform);
	view_->AddSubview(new he::ui::ImageView(&img_factory, vertex_.Get(), texture_.Get()));
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

///EOF
