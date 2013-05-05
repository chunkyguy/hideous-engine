//
//  RectTextTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "RectTextTest.h"

#include <he/EventLoop/Gesture.h>
#include <he/Font/Font.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Screen.h>
#include <he/Utils/Utils.h>

RectTextTest::~RectTextTest(){
	unload_text();
}

RectTextTest::RectTextTest(double w, double h) :
font_(0),
text_(0)
{
		FILE_LOG(logDEBUG) <<"{" <<w << "," << h << "}";
		//<<"{" << he::g_Screen.width/2 << "," << he::g_Screen.height << "}";
		
		//setup globals
		//debugger
		const std::string loglevel("DEBUG1");
		FILELog::ReportingLevel() = FILELog::FromString(loglevel);
		FILE_LOG(logDEBUG) << "Logging Enabled: RectTextTest" << loglevel << std::endl;
		//random
		srand(time(NULL));
		//screen constants
		he::g_Screen = he::Screen(w, h);
		
		//start things here
		//waiting for input
}

void RectTextTest::Update(double dt){
	handle_gestures();
}
void RectTextTest::Render(){	
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

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
	text_ = new he::Text("Whacky ?!",  GLKVector2Make(-100,0), GLKVector4Make(0.0, 0.0, 0.0, 1.0));
	font_->LoadText(text_);
}

void RectTextTest::unload_text(){
	delete font_; font_ = 0;
	delete text_; text_ = 0;
}

void RectTextTest::handle_gestures(){
	if(he::g_Gesture.action_ == he::Gesture::kTap){
		load_text();
		he::g_Gesture.Reset();
	}
}

//EOF