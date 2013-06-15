//
//  RectTextTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "RectTextTest.h"

#include <he/Font/Font.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Utils.h>

RectTextTest::~RectTextTest(){
	unload_text();
	
	he::g_EventLoop->RemoveListener(gesture_listener_);
	delete gesture_listener_;
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
	
		//waiting for input
}

void RectTextTest::update(float dt){
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
	font_ = new he::Font("Silom.ttf", 48);
	he::Transform trans;
	trans.SetPosition(GLKVector2Make(-100,0));
	text_ = new he::Text("Whacky ?!", trans, GLKVector4Make(0.0, 0.0, 0.0, 1.0));
	font_->LoadText(text_);
}

void RectTextTest::unload_text(){
	delete font_; font_ = 0;
	delete text_; text_ = 0;
}

void RectTextTest::HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ == he::Gesture::kTap){
		load_text();
	}
}

//EOF