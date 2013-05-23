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
GestureTest::GestureTest(double width, double height) :
gesture_listner_(nullptr)
{
	//setup globals
	he::GlobalsInit(width, height);

	//debugger
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "Logging Enabled: " << loglevel << std::endl;
	FILE_LOG(logDEBUG) <<"{" << width << "," << height << "}";

	//random
	srand(time(NULL));
	
	gesture_listner_ = new he::GestureListener<GestureTest>(this, &GestureTest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listner_);
	
	//start things here
}
GestureTest::~GestureTest(){
	he::g_EventLoop->RemoveListener(gesture_listner_);
	delete gesture_listner_;
	
	he::GlobalsDestroy();
}

void GestureTest::Update(double dt){
	obj_.Update(dt);
}

void GestureTest::Render(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
		
	obj_.Render();
}

//	Long press = movement
void GestureTest::HandleGesture(const he::Gesture &gesture){
	switch(gesture.action_){
			
		case he::Gesture::kTap:{
			if(gesture.continious_){
				obj_.SetDirection(he::g_Screen->MapPointToGrid(gesture.GetHitPoint()));
			}else{
				GLKVector4 clr = GLKVector4Make(0.0, 0.0, 0.0, 1.0);
				switch(he::g_Screen->MapPointToGrid(gesture.GetHitPoint())){
					case he::Screen::Grid::kTopLeft:		clr.r = 0.3;break;
					case he::Screen::Grid::kTop:			clr.r = 0.6;break;
					case he::Screen::Grid::kTopRight:		 clr.r = 1.0;break;
						
					case he::Screen::Grid::kLeft:			 clr.g = 0.3;break;
					case he::Screen::Grid::kCenter:		 clr.g = 0.6;break;
					case he::Screen::Grid::kRight:			 clr.g = 1.0;break;
						
					case he::Screen::Grid::kBottomLeft:	 clr.b = 0.3;break;
					case he::Screen::Grid::kBottom:		 clr.b = 0.6;break;
					case he::Screen::Grid::kBottomRight:	 clr.b = 1.0;break;
						
					case he::Screen::Grid::kUnknown:		 break;
				}
				obj_.SetColor(clr);
			}
		}			break;
			
		case he::Gesture::kZoomIn:
			break;
			
		case he::Gesture::kZoomOut:
			break;
			
		case he::Gesture::kDrag:
			break;
			
		case he::Gesture::kLongTap:
			break;
			
		case he::Gesture::kNone:{
			obj_.SetDirection(he::Screen::Grid::kUnknown);
		}	break;
	}
}
///EOF
