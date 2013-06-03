//
//  TextureBigBangTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 04/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "TextureBigBangTest.h"

#include	 <he/RenderObject/RenderObject.h>
#include <he/Shaders/RectTextureSh/RectTextureSh.h>
#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Utils.h>
#include <he/Vertex/VertexTex.h>

TextureBigBangTest::~TextureBigBangTest(){
	unload_assets();
	
	he::g_EventLoop->RemoveListener(gesture_listener_);
	delete gesture_listener_;

	he::GlobalsDestroy();
}

TextureBigBangTest::TextureBigBangTest(float w, float h){
	//setup globals
	he::GlobalsInit(w, h);
	
	//debugger
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "Logging Enabled: " << loglevel << std::endl;
	FILE_LOG(logDEBUG) <<"{" <<w << "," << h << "}";

	//random
	srand(time(NULL));

	load_assets();
	
	gesture_listener_ = new he::GestureListener<TextureBigBangTest>(this, &TextureBigBangTest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listener_);
	
	state_ = kDead;
}


void TextureBigBangTest::load(GLKVector2 at){
	FILE_LOG(logDEBUG) << "load";
	squares_ = new TexturedSprite *[kTotal_tex_sprites];
	for(int i = 0; i < kTotal_tex_sprites; i++){
		squares_[i] = new TexturedSprite;
		squares_[i]->Init(i, sprite_, at);
	}
	state_ = kRunning;
	delay_ = 0.0;
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}
void TextureBigBangTest::unload(){
	FILE_LOG(logDEBUG) << "unload";
	for(int i = 0; i < kTotal_tex_sprites; i++){
		if(squares_[i]){
			delete squares_[i];
			squares_[i] = 0;
		}
	}
	delete [] squares_;
	state_ = kDead;
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void TextureBigBangTest::Update(float dt){
	
	if(state_ != kRunning){
		return;
	}
	
	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for(int i = 0; i < kTotal_tex_sprites; ++i){
		if(squares_[i]){
			switch(squares_[i]->GetLifeState()){
				case TexturedSprite::kZombie:	squares_[i]->SetDead();			break;
				case TexturedSprite::kLiving:	squares_[i]->Update(dt);			break;
				case TexturedSprite::kDead:		delete squares_[i]; squares_[i] = 0;		break;
			}
			sprite_->Render();
		}
	}
	
	//delay = 0.0125;
}
void TextureBigBangTest::Render(){
	if(state_ != kRunning){
		return;
	}
	
	//	k.Render();
}

void TextureBigBangTest::HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ == he::Gesture::kTap){
		switch(state_){
			case kRunning:
				unload();
				break;
				
			case kDead:
				load(gesture.GetHitPoint());
				break;
		}
	}
}

void TextureBigBangTest::load_assets(){
	texture_ = new he::Texture(he::ResourcePath() + "clock.png");
	vertex_data_ = new he::VertexTex(50, 50);
	shader_ = new he::RectTextureSh;
	sprite_ = new he::RenderObject(vertex_data_, shader_, texture_);
}
void TextureBigBangTest::unload_assets(){
	delete texture_;
	delete vertex_data_;
	delete shader_;
	delete sprite_;
}
//EOF