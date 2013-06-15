//
//  AnimationTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 01/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "AnimationTest.h"

#include <OpenGLES/ES2/gl.h>

#include <he/Animation/AnimationLoop.h>
#include <he/Shaders/ColorShader.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Utils.h>

AnimationTest::~AnimationTest(){
	if(objects_){
		unload();
	}
	he::g_EventLoop->RemoveListener(gesture_listner_);
	delete gesture_listner_;
}

AnimationTest::AnimationTest() :
kObjects_(2),
objects_(nullptr),
active_object_(-1),
gesture_listner_(nullptr)
{}

void AnimationTest::init(){
	//debugger
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "AnimationTest Logging Enabled: " << loglevel << std::endl;
	
	gesture_listner_ = new he::GestureListener<AnimationTest>(this, &AnimationTest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listner_);
	
	
}

void AnimationTest::update(float dt){
	if(objects_){
		for (int i = 0; i < kObjects_; ++i) {
			objects_[i]->Update(dt);
		}
	}
}
void AnimationTest::render(){
	if(objects_){
		for (int i = 0; i < kObjects_; ++i) {
			objects_[i]->Render();
		}
	}
}

void AnimationTest::HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ == he::Gesture::kTap && gesture.state_ == he::Gesture::kEnd){
		if(objects_){
			GLKVector2 pt = gesture.GetHitPoint();
			objects_[active_object_++]->TouchEnd(pt);
			if(active_object_ >= kObjects_){
				active_object_ = 0;
			}
		}else{
			load();
		}
	}
}

void AnimationTest::load(){
	if(objects_){
		unload();
	}
	shader_ = new he::ColorShader;
	objects_ = new AnimObj* [kObjects_];
	for(int i = 0; i < kObjects_; ++i){
		objects_[i] = new AnimObj(i+1, shader_);
	}
	active_object_ = 0;
}
void AnimationTest::unload(){
	for(int i = 0; i < kObjects_; ++i){
		delete objects_[i];
	}
	delete [] objects_; objects_ = nullptr;
	active_object_ = -1;
	delete shader_;
}
////EOF
