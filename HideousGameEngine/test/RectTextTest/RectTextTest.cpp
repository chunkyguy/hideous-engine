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
font_(0){
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
	
	if(font_){
		std::list<he::GlyphData *> gd = font_->GetGlyph();
		
		GLKVector2 pos = GLKVector2Make(-100,0);
		GLKMatrix4 tMat;
		GLKMatrix4 mvpMat;
		
		for(std::list<he::GlyphData *>::iterator it = gd.begin(); it != gd.end(); ++it){
			he::RenderObject *r = (*it)->render_object_;
			//pos = (*it)->position;
			tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
			mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
			r->mvp_ = mvpMat;
			//r->clr = GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 1.0);	// Epilepsy warning
			r->Render();
		}
	}
}

void RectTextTest::load_text(){
	if(font_){
		unload_text();
	}
	//Draw a text
	font_ = new he::Font("Silom.ttf", 48, GLKVector4Make(0.0, 0.0, 0.0, 1.0));
	font_->LoadGlyph("Whacky?!");
}

void RectTextTest::unload_text(){
	delete font_; font_ = 0;
}

void RectTextTest::handle_gestures(){
	if(he::g_Gesture.action_ == he::Gesture::kTap){
		load_text();
		he::g_Gesture.Reset();
	}
}

//EOF