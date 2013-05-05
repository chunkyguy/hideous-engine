//
//  MultiFontTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 24/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "MultiFontTest.h"

#include <he/EventLoop/Gesture.h>
#include <he/Font/Font.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Screen.h>
#include <he/Utils/Utils.h>

MultiFontTest::~MultiFontTest(){
	unload_text();
}

MultiFontTest::MultiFontTest(double w, double h) :
courier_(0),
simsun_(0),
whacky_(0),
labs_(0)
{
	FILE_LOG(logDEBUG) <<"{" <<w << "," << h << "}";
	//<<"{" << he::g_Screen.width/2 << "," << he::g_Screen.height << "}";
	
	//setup globals
	//debugger
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "Logging Enabled: MultiFontTest" << loglevel << std::endl;
	//random
	srand(time(NULL));
	//screen constants
	he::g_Screen = he::Screen(w, h);
	//start things here
	//waiting for input
}

void MultiFontTest::Update(double dt){
	handle_gestures();
}
void MultiFontTest::Render(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
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
	
	whacky_ = new he::Text("Whacky", GLKVector2Make(-100, 100),  GLKVector4Make(0.0, 0.0, 0.0, 1.0));
	courier_->LoadText(whacky_);
	
	labs_ = new he::Text("Labs", GLKVector2Make(-100, -100), GLKVector4Make(0.0,0.0,0.0,1.0));
	simsun_->LoadText(labs_);
}

void MultiFontTest::unload_text(){
	delete courier_; courier_ = 0;
	delete simsun_; simsun_ = 0;
	delete whacky_; whacky_ = 0;
	delete labs_; labs_ = 0;
}

void MultiFontTest::handle_gestures(){
	if(he::g_Gesture.action_ == he::Gesture::kTap){
		load_text();
		he::g_Gesture.Reset();
	}
}

////EOF
