//
//  RectTextTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "RectTextTest.h"

#include <he/Font/Font.h>
#include <he/UI/Text.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/TextShader.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Utils.h>
#include <he/Utils/ResourcePath.hpp>

RectTextTest::~RectTextTest(){
	unload_text();
	
	he::g_EventLoop->RemoveListener(gesture_listener_);
	delete gesture_listener_;
	delete shader_;
}

RectTextTest::RectTextTest() :
font_(nullptr),
text_(nullptr),
gesture_listener_(nullptr)
{}

void RectTextTest::init(){
		//debugger
		const std::string loglevel("DEBUG1");
		FILELog::ReportingLevel() = FILELog::FromString(loglevel);
		FILE_LOG(logDEBUG) << "Logging Enabled: RectTextTest" << loglevel << std::endl;

		//random
		srand(time(NULL));
		
	gesture_listener_ = new he::GestureListener<RectTextTest>(this, &RectTextTest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listener_);
	
	shader_ = new he::TextShader;
	
		//waiting for input
}

void RectTextTest::update(float dt){
	if(text_){
		text_->Update(dt);
	}
}
void RectTextTest::render(){
	if(text_){
		text_->Render();
	}
}

void RectTextTest::load_text(){
	if(font_){
		unload_text();
	}
	//Draw a text
	font_ = new he::Font(he::ResourcePath() + "Silom.ttf", 18);
	
	assert(font_);
	assert(shader_);
	factory_ = new he::TextFactory(font_, shader_);
	
	he::Frame frame(he::Transform_Create(GLKVector2Make(-220.0f, 0.0f)));
	text_ = new he::Text(frame, factory_, "The quick brown fox jumps over the lazy dog", GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 1.0));
}

void RectTextTest::unload_text(){
	delete font_; font_ = 0;
	delete factory_; factory_ = 0;
	delete text_; text_ = 0;
}

void RectTextTest::HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ == he::Gesture::kTap && gesture.state_ == he::Gesture::kEnd){
		load_text();
	}
}

//EOF