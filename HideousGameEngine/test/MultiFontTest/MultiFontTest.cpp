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
simsun_(0)
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
	
	if(courier_){
		std::list<he::GlyphData *> gd = courier_->GetGlyph();
		GLKVector2 pos = GLKVector2Make(-100,100);
		
		GLKMatrix4 tMat;
		GLKMatrix4 mvpMat;
		for(std::list<he::GlyphData *>::iterator it = gd.begin(); it != gd.end(); ++it){
			he::RenderObject *r = (*it)->render_object_;
			tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
			mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
			r->mvp_ = mvpMat;
			r->Render();
		}
	}
	
	if(simsun_){
		std::list<he::GlyphData *> gd = simsun_->GetGlyph();
		GLKVector2 pos = GLKVector2Make(-100,-100);
		
		GLKMatrix4 tMat;
		GLKMatrix4 mvpMat;
		for(std::list<he::GlyphData *>::iterator it = gd.begin(); it != gd.end(); ++it){
			he::RenderObject *r = (*it)->render_object_;
			tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
			mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
			r->mvp_ = mvpMat;
			r->Render();
		}
	}

}

void MultiFontTest::load_text(){
	if(courier_){
		unload_text();
	}
	
	courier_ = new he::Font("Courier New.ttf", 32, GLKVector4Make(0.0, 0.0, 0.0, 1.0));
	courier_->LoadGlyph("Whacky?!");
	
	simsun_ = new he::Font("SimSun.ttf", 32, GLKVector4Make(0.0,0.0,0.0,1.0));
	simsun_->LoadGlyph("Whacky?!");
}

void MultiFontTest::unload_text(){
	delete courier_; courier_ = 0;
	delete simsun_; simsun_ = 0;
}

void MultiFontTest::handle_gestures(){
	if(he::g_Gesture.action_ == he::Gesture::kTap){
		load_text();
		he::g_Gesture.Reset();
	}
}

////EOF
