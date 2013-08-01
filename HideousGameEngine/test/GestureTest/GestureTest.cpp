//
//  GestureTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 25/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "GestureTest.h"

#include <he/Utils/GLKMath_Additions.h>
#include <OpenGLES/ES2/gl.h>

#include <he/Utils/DebugLog.h>
#include <he/Utils/Utils.h>

namespace {
	void PrintGesture(const he::Gesture &gesture){
		std::string action = "";
		switch (gesture.action_) {
			case he::Gesture::kTap: action = "Tap"; break;
				//			case he::Gesture::kLongTap: action = "LongTap"; break;
			case he::Gesture::kZoomIn: action = "ZoomIn"; break;
			case he::Gesture::kZoomOut: action = "ZoomOut"; break;
			case he::Gesture::kDrag: action = "Drag"; break;
			case he::Gesture::kNone:
			default:
				action = "UNKNOWN"; break;
		}
		
		std::string state = "";
		switch (gesture.state_) {
			case he::Gesture::kBegin: state =  "Begin"; break;
			case he::Gesture::kChange: state = "Change"; break;
			case he::Gesture::kEnd: state = "End"; break;
			case he::Gesture::kCancel: state = "Cancel"; break;
			case he::Gesture::kFail: state = "Fail"; break;
			case he::Gesture::kPossible: state = "Possible"; break;
			default: state = "UNKNOWN"; break;
		}
		
		FILE_LOG(logDEBUG) << "Gesture:" << std::endl
		<< "Action: " << action << std::endl
		<< "Continous: " << (gesture.continious_?"Y":"N") << std::endl
		<< "Fingers: " << gesture.fingers_ << std::endl
		<< "State: " << state << std::endl
		<< "Taps: " << gesture.taps_ << std::endl
		<< "TouchPoint(UI coord space): {" << gesture.touch_point_.x << "," << gesture.touch_point_.y << "}" << std::endl
		<< "HitPoint(GL coord space): {" << gesture.GetHitPoint().x << "," << gesture.GetHitPoint().y << "}" << std::endl
		<< "Velocity: {" << gesture.velocity_.x << "," << gesture.velocity_.y << "}" << std::endl;
	}
}

GestureTest::GestureTest() :
gesture_listner_(nullptr)
{}

void GestureTest::init(){
	//random
	srand(time(NULL));

	//gesture_listner_ = he::CreateGestureListener<GestureTest>(this, &GestureTest::HandleGesture);
	gesture_listner_ = new he::GestureListener<GestureTest>(this, &GestureTest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listner_);
	
	//start things here
	obj_ = new GObj;
}
GestureTest::~GestureTest(){
	delete obj_;

	//he::DestroyGestureListener(gesture_listner_);
	he::g_EventLoop->RemoveListener(gesture_listner_);
	delete gesture_listner_;
}

void GestureTest::update(float dt){
	obj_->Update(dt);
}

void GestureTest::render(){
	obj_->Render();
}

//	Long press = movement
void GestureTest::HandleGesture(const he::Gesture &gesture){
	PrintGesture(gesture);
	
	switch(gesture.action_){
		case he::Gesture::kTap:{
			if(gesture.continious_){
				obj_->SetDirection(he::g_Screen->MapPointToGrid(gesture.GetHitPoint()));
			}else{
				GLKVector4 clr = GLKVector4Make(0.0, 0.0, 0.0, 1.0);
				switch(he::g_Screen->MapPointToGrid(gesture.GetHitPoint())){
					case he::Screen::Grid::kTopLeft:		clr.r = 0.3;break;
					case he::Screen::Grid::kTop:			clr.r = 0.6;break;
					case he::Screen::Grid::kTopRight:	 clr.r = 1.0;break;
						
					case he::Screen::Grid::kLeft:			 clr.g = 0.3;break;
					case he::Screen::Grid::kCenter:		 clr.g = 0.6;break;
					case he::Screen::Grid::kRight:			 clr.g = 1.0;break;
						
					case he::Screen::Grid::kBottomLeft:	 clr.b = 0.3;break;
					case he::Screen::Grid::kBottom:		 clr.b = 0.6;break;
					case he::Screen::Grid::kBottomRight:	 clr.b = 1.0;break;
						
					case he::Screen::Grid::kUnknown:		 break;
				}
				obj_->SetColor(clr);
			}
		}			break;
			
		case he::Gesture::kZoomIn:
			break;
			
		case he::Gesture::kZoomOut:
			break;
			
		case he::Gesture::kDrag:
			break;
			
//		case he::Gesture::kLongTap:
//			break;
			
		case he::Gesture::kNone:{
			obj_->SetDirection(he::Screen::Grid::kUnknown);
		}	break;
	}
}

///EOF
