//
//  TextureBigBangTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 04/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "TextureBigBangTest.h"

#include	 <he/RenderObject/RenderObject.h>
#include <he/Shaders/TextureShader.h>
#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Utils.h>
#include <he/Vertex/TextureVertex.h>

TextureBigBangTest::TextureBigBangTest(){}

void TextureBigBangTest::init(){
	//debugger
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "Logging Enabled: " << loglevel << std::endl;

	//random
	srand(time(NULL));

	load_assets();
	
	gesture_listener_ = new he::GestureListener<TextureBigBangTest>(this, &TextureBigBangTest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listener_);
	
	state_ = kDead;
}

TextureBigBangTest::~TextureBigBangTest(){
	unload_assets();
	
	he::g_EventLoop->RemoveListener(gesture_listener_);
	delete gesture_listener_;
}

void TextureBigBangTest::load(GLKVector2 at){
	FILE_LOG(logDEBUG) << "load";
	he::Transform trans(GLKVector3Make(0.0f, 0.0f, 0.0f));
	trans.SetPosition(at);
	squares_ = new TexturedSprite *[kTotal_tex_sprites];
	for(int i = 0; i < kTotal_tex_sprites; i++){
		squares_[i] = new TexturedSprite;
		squares_[i]->Init(i, sprite_, trans);
	}
	state_ = kRunning;
	delay_ = 0.0;
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
}

void TextureBigBangTest::update(float dt){
	
	if(state_ != kRunning){
		return;
	}

	//delay = 0.0125;
}
void TextureBigBangTest::render(){
	if(state_ != kRunning){
		return;
	}

	for(int i = 0; i < kTotal_tex_sprites; ++i){
		if(squares_[i]){
			switch(squares_[i]->GetLifeState()){
				case TexturedSprite::kZombie:	squares_[i]->SetDead();			break;
				case TexturedSprite::kLiving:	squares_[i]->Update();			break;
				case TexturedSprite::kDead:		delete squares_[i]; squares_[i] = 0;		break;
			}
			sprite_->Render();
		}
	}

	//	k.Render();
}

void TextureBigBangTest::HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ == he::Gesture::kTap && gesture.state_ == he::Gesture::kEnd){
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
	GLKVector2 size = GLKVector2Make(50, 50);
	vertex_data_ = new he::TextureVertex(size);
	shader_ = new he::TextureShader;
	sprite_ = new he::RenderObject(vertex_data_, shader_, texture_);
}
void TextureBigBangTest::unload_assets(){
	delete texture_;
	delete vertex_data_;
	delete shader_;
	delete sprite_;
}
//EOF