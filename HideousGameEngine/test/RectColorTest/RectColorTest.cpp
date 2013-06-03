//
//  RectColorTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 10/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "RectColorTest.h"

#include <he/Shaders/RectColorSh/RectColorSh.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Utils.h>

RectColorTest::~RectColorTest(){
	delete shader_;
	he::g_EventLoop->RemoveListener(gesture_listner_);
	delete gesture_listner_;
	
	he::GlobalsDestroy();
}
RectColorTest::RectColorTest(float w, float h) :
squares_(0),
shader_(new he::RectColorSh)
{
	// Init globals
	he::GlobalsInit(w, h);

	//debugger
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "Logging Enabled: RectColorTest " << loglevel << std::endl;
	FILE_LOG(logDEBUG) <<"{" <<w << "," << h << "}";

	//random
	srand(time(NULL));


	gesture_listner_ = new he::GestureListener<RectColorTest>(this, &RectColorTest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listner_);
	
	// waiting for gesture
}


void RectColorTest::Update(float dt){

	if(!squares_){
		return;
	}

	int deadsq = 0;
	for(int i = 0; i < kTotal_squares; i++){
		switch(squares_[i]->GetLifeState()){
			case RunningSquare::kZombie:		squares_[i]->SetDead();		break;
			case RunningSquare::kLiving:		squares_[i]->Update(dt);	break;
			case RunningSquare::kDead:		deadsq++;		break;
		}
	}
	if(deadsq == kTotal_squares){
		unload_squares();
	}
}
void RectColorTest::Render(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	if(!squares_){
		return;
	}

	for(int i = 0; i < kTotal_squares; i++){
		if(squares_[i]->GetLifeState() == RunningSquare::kLiving){
			squares_[i]->Render();
		}
	}
}

void RectColorTest::load_squares(){
	if(squares_){
		unload_squares();
	}
	

	squares_ = new RunningSquare *[kTotal_squares];
	for(int i = 0; i < kTotal_squares; ++i){
		squares_[i] = new RunningSquare(shader_);
	}
}
void RectColorTest::unload_squares(){
	for(int i = 0; i < kTotal_squares; ++i){
		delete squares_[i];
	}
	delete [] squares_;
	squares_ = 0;
	//	Optional:
	//	Can call this here to release all assets
	//	will get loaded again at next instance of RectColor
	//	he::RectColor::cleanAsset();
}
void RectColorTest::	HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ == he::Gesture::kTap){
		load_squares();
	}
}

//EOF