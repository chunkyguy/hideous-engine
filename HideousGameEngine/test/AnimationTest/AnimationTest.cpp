//
//  AnimationTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 01/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "AnimationTest.h"

#include <OpenGLES/ES2/gl.h>

#include <he/Utils/DebugLog.h>
#include <he/Utils/Screen.h>
#include <he/EventLoop/Gesture.h>

AnimationTest::~AnimationTest(){
	if(anim_obj_){
		unload();
	}
}

AnimationTest::AnimationTest(double width, double height) :
anim_obj_(0)
{
	//setup globals
	//debugger
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "AnimationTest Logging Enabled: " << loglevel << std::endl;
	he::g_Screen = he::Screen(width, height);
}

void AnimationTest::Update(double dt){
	handle_gesture();
	if(anim_obj_){
		anim_obj_->Update(dt);
	}
}
void AnimationTest::Render(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if(anim_obj_){
		anim_obj_->Render();
	}
}

void AnimationTest::handle_gesture(){
	if(he::g_Gesture.action_ != he::Gesture::kTap){
		return;
	}
	if(anim_obj_){
		GLKVector2 pt = he::g_Gesture.GetHitPoint();
		anim_obj_->TouchEnd(pt);
	}else{
		load();
	}
	he::g_Gesture.Reset();
}

void AnimationTest::load(){
	if(anim_obj_){
		unload();
	}
	anim_obj_ = new AnimObj;
}
void AnimationTest::unload(){
	delete anim_obj_; anim_obj_ = 0;
}
////EOF
