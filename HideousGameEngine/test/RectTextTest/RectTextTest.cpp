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
text_small_(nullptr),
text_caps_(nullptr),
text_nums_(nullptr),
text_sp_(nullptr),
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
	if(text_small_){
		text_small_->Update(dt);
		text_caps_->Update(dt);
		text_nums_->Update(dt);
		text_sp_->Update(dt);
	}
}
void RectTextTest::render(){
	if(text_small_){
		text_small_->Render();
		text_caps_->Render();
		text_nums_->Render();
		text_sp_->Render();
	}
}

void RectTextTest::load_text(){
	if(factory_){
		unload_text();
	}
	//Draw a text
	assert(shader_);
	factory_ = new he::TextViewFactory(shader_, new he::Font(he::ResourcePath() + "Courier New.ttf", 14));
	text_caps_ = factory_->CreateTextView(he::Transform_Create(GLKVector3Make(0.0f, -50.0f, he::g_Screen->z_)), "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");
	text_small_ = factory_->CreateTextView(he::Transform_Create(GLKVector3Make(0.0f, 0.0f, he::g_Screen->z_)), "the quick brown fox jumps over the lazy dog");
	text_nums_ = factory_->CreateTextView(he::Transform_Create(GLKVector3Make(0.0f, 50.0f, he::g_Screen->z_)), "0123456789");
	text_sp_ = factory_->CreateTextView(he::Transform_Create(GLKVector3Make(0.0f, 100.0f, he::g_Screen->z_)), "~!@#$%^&*()_+-={}\\|;:'\"<>?,./");
}

void RectTextTest::unload_text(){
	delete factory_; factory_ = 0;
	delete text_small_; text_small_ = 0;
	delete text_caps_; text_caps_ = 0;
	delete text_nums_; text_nums_ = 0;
	delete text_sp_; text_sp_ = 0;
}

void RectTextTest::HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ == he::Gesture::kTap && gesture.state_ == he::Gesture::kEnd){
		load_text();
	}
}

//EOF