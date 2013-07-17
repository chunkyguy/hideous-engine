//
//  MultiFontTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 24/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "MultiFontTest.h"

#include <he/Font/Font.h>
#include <he/UI/Text.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/TextShader.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Transform.h>
#include <he/Utils/Utils.h>
#include <he/Utils/ResourcePath.hpp>

MultiFontTest::~MultiFontTest(){
	unload_text();
	he::g_EventLoop->RemoveListener(gesture_listner_);
	delete gesture_listner_;
	delete shader_;
}

MultiFontTest::MultiFontTest() :
courier_factory_(nullptr),
simsun_factory_(nullptr),
whacky_(nullptr),
labs_(nullptr),
gesture_listner_(nullptr),
shader_(nullptr)
{}

void MultiFontTest::init(){

	//random
	srand(time(NULL));

	
	gesture_listner_ = new he::GestureListener<MultiFontTest>(this, &MultiFontTest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listner_);

	shader_ = new he::TextShader;
	//waiting for input
}

void MultiFontTest::update(float dt){
	if(whacky_){
		whacky_->Update(dt);
	}
	
	if(labs_){
		labs_->Update(dt);
	}
}
void MultiFontTest::render(){
	
	if(whacky_){
		whacky_->Render();
	}
	
	if(labs_){
		labs_->Render();
	}

}

void MultiFontTest::load_text(){
	if(courier_factory_){
		unload_text();
	}

	
	courier_factory_ = new he::TextViewFactory(shader_, new he::Font(he::ResourcePath() + "Courier New.ttf", 32));
	simsun_factory_ = new he::TextViewFactory(shader_, new he::Font(he::ResourcePath() + "SimSun.ttf", 32));
	
	whacky_ = simsun_factory_->CreateTextView(he::Transform_Create(GLKVector2Make(-100.0f, 100.0f)), "Whacky");
	labs_ = courier_factory_->CreateTextView(he::Transform_Create(GLKVector2Make(-100.0f, -100.0f)), "Labs");
}

void MultiFontTest::unload_text(){
	delete courier_factory_; courier_factory_ = 0;
	delete simsun_factory_; simsun_factory_ = 0;
	delete whacky_; whacky_ = 0;
	delete labs_; labs_ = 0;
}

void MultiFontTest::HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ == he::Gesture::kTap && gesture.state_ == he::Gesture::kEnd){
		load_text();
	}
}

////EOF
