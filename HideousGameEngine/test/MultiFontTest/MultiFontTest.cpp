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
courier_(nullptr),
simsun_(nullptr),
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
	if(courier_){
		unload_text();
	}

	
	courier_ = new he::Font(he::ResourcePath() + "Courier New.ttf", 32);
	simsun_ = new he::Font(he::ResourcePath() + "SimSun.ttf", 32);
	
	whacky_txt_ = new he::Text(shader_, courier_, "Whacky");
	whacky_ = new he::TextView(he::Transform_Create(GLKVector2Make(-100.0f, 100.0f)), whacky_txt_);

	labs_txt_ = new he::Text(shader_, simsun_, "Labs");
	labs_ = new he::TextView(he::Transform_Create(GLKVector2Make(-100.0f, -100.0f)), labs_txt_);
}

void MultiFontTest::unload_text(){
	delete courier_; courier_ = 0;
	delete simsun_; simsun_ = 0;
	
	delete whacky_txt_; whacky_txt_ = 0;
	delete whacky_; whacky_ = 0;

	delete labs_txt_; labs_txt_= 0;
	delete labs_; labs_ = 0;
}

void MultiFontTest::HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ == he::Gesture::kTap && gesture.state_ == he::Gesture::kEnd){
		load_text();
	}
}

////EOF
