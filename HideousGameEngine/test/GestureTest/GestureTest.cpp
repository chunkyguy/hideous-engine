//
//  GestureTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 25/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "GestureTest.h"

#include <GLKit/GLKMath.h>
#include <OpenGLES/ES2/gl.h>

#include <he/EventLoop/Gesture.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Screen.h>

GestureTest::GestureTest(double width, double height){
	FILE_LOG(logDEBUG) <<"{" << width << "," << height << "}";
	//<<"{" << he::g_Screen.width/2 << "," << he::g_Screen.height << "}";
	
	//setup globals
	//debugger
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "Logging Enabled: " << loglevel << std::endl;
	//random
	srand(time(NULL));
	//screen constants
	he::g_Screen = he::Screen(width, height);
	//start things here
}

void GestureTest::Update(double dt){
	handle_gesture();
	obj_.Update(dt);
}

void GestureTest::Render(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
		
	obj_.Render();
}

//	Long press = movement
void GestureTest::handle_gesture(){
	switch(he::g_Gesture.action_){
			
		case he::Gesture::kTap:{
			if(he::g_Gesture.continious_){
				obj_.SetDirection(he::g_Screen.MapPointToGrid(he::g_Gesture.GetHitPoint()));
			}else{
				GLKVector4 clr = GLKVector4Make(0.0, 0.0, 0.0, 1.0);
				switch(he::g_Screen.MapPointToGrid(he::g_Gesture.GetHitPoint())){
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
				he::g_Gesture.Reset();
			}
		}			break;
			
		case he::Gesture::kZoomIn:
			break;
			
		case he::Gesture::kZoomOut:
			break;
			
		case he::Gesture::kDrag:
			break;
			
		case he::Gesture::kNone:{
			obj_.SetDirection(he::Screen::Grid::kUnknown);
		}	break;
	}
}
///EOF
