//
//  MultiFontTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 24/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "MultiFontTest.h"

#include <he/Font/Font.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Transform.h>
#include <he/Utils/Utils.h>

MultiFontTest::~MultiFontTest(){
	unload_text();
	he::g_EventLoop->RemoveListener(gesture_listner_);
	delete gesture_listner_;
}

MultiFontTest::MultiFontTest() :
courier_(nullptr),
simsun_(nullptr),
whacky_(nullptr),
labs_(nullptr),
gesture_listner_(nullptr)
{}

void MultiFontTest::init(){

	//random
	srand(time(NULL));

	
	gesture_listner_ = new he::GestureListener<MultiFontTest>(this, &MultiFontTest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listner_);
	
	//waiting for input
}

void MultiFontTest::update(float dt){
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
	
	courier_ = new he::Font("Courier New.ttf", 32);
	simsun_ = new he::Font("SimSun.ttf", 32);
	
	he::Transform trans(GLKVector3Make(0.0f, 0.0f, 0.0f));
	trans.SetPosition(GLKVector2Make(-100, 100));
	whacky_ = new he::Text("Whacky", trans,  GLKVector4Make(0.0, 0.0, 0.0, 1.0));
	courier_->LoadText(whacky_);

	trans.SetPosition(GLKVector2Make(-100, -100));
	labs_ = new he::Text("Labs", trans, GLKVector4Make(0.0,0.0,0.0,1.0));
	simsun_->LoadText(labs_);
}

void MultiFontTest::unload_text(){
	delete courier_; courier_ = 0;
	delete simsun_; simsun_ = 0;
	delete whacky_; whacky_ = 0;
	delete labs_; labs_ = 0;
}

void MultiFontTest::HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ == he::Gesture::kTap){
		load_text();
	}
}

////EOF
