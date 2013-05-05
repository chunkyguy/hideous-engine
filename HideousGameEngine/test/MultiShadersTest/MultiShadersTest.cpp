//
//  MultiShadersTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 19/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "MultiShadersTest.h"

#include <string>
#include <algorithm>

#include <he/EventLoop/Gesture.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Screen.h>
#include <he/Utils/Utils.h>

MultiShadersTest::~MultiShadersTest(){
	unload_objects();
}

MultiShadersTest::MultiShadersTest(double w, double h) :
factory_(0),
color_object_(0),
texture_object_(0),
text_object_(0)
{
	//setup globals
	//debugger
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "MultiShadersTest Logging Enabled: " << loglevel << std::endl;
	he::g_Screen = he::Screen(w, h);

	//start things here
	load_indx_[0] = 0;
	load_indx_[1] = 1;
	load_indx_[2] = 2;
	srand(time(NULL));
	
	//waiting for input
}
void MultiShadersTest::Render(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if(factory_){
		for(int i = 0; i < 3; ++i){
			switch(load_indx_[i]){
				case 0: color_object_->Render(); break;
				case 1: 	texture_object_->Render(); break;
				case 2: text_object_->Render(); break;
			}
		}
	}
}


void MultiShadersTest::Update(double dt){
	handle_gestures();
}

void MultiShadersTest::load_objects(){
	if(factory_){
		unload_objects();
	}
	
	factory_ = new ObjectFactory;
	
	for(int i = 0; i < 3; ++i){
		switch(load_indx_[i]){
			case 0:
				FILE_LOG(logDEBUG) << "create Colored Obj";
				color_object_ = factory_->CreateColoredObject();
				break;
				
			case 1:
				FILE_LOG(logDEBUG) << "create Texture Obj";
				texture_object_ = factory_->CreateTexturedObject();
				break;
				
			case 2:
				FILE_LOG(logDEBUG) << "create Text Obj";
				text_object_ = factory_->CreateTextObject();
				break;
		}
	}

	std::next_permutation(load_indx_, load_indx_+3);
}

void MultiShadersTest::unload_objects(){
	delete color_object_; color_object_ = 0;
	delete texture_object_; texture_object_ = 0;
	delete text_object_; text_object_ = 0;
	delete factory_; factory_ = 0;
}

void MultiShadersTest::handle_gestures(){
	if(he::g_Gesture.action_ == he::Gesture::kTap){
		load_objects();
		he::g_Gesture.Reset();
	}
}
//EOF
