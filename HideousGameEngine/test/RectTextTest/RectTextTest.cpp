//
//  RectTextTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "RectTextTest.h"

#include <he/Font/Font.h>
#include <he/UI/Text.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/TextShader.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Utils.h>
#include <he/Utils/ResourcePath.hpp>

RectTextTest::~RectTextTest(){
	unload_text();
	
	he::g_EventLoop->RemoveListener(gesture_listener_);
	delete gesture_listener_;
	delete shader_;
	delete font_;
}

RectTextTest::RectTextTest() :
text_small_(nullptr),
text_caps_(nullptr),
text_nums_(nullptr),
text_sp_(nullptr),
gesture_listener_(nullptr)
{}

void RectTextTest::init(){
		//debugger
		const std::string loglevel("DEBUG1");
		FILELog::ReportingLevel() = FILELog::FromString(loglevel);
		FILE_LOG(logDEBUG) << "Logging Enabled: RectTextTest" << loglevel << std::endl;

		//random
		srand(time(NULL));
		
	gesture_listener_ = new he::GestureListener<RectTextTest>(this, &RectTextTest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listener_);
	
	shader_ = new he::TextShader;
	font_ = new he::Font(he::ResourcePath() + "Courier New.ttf", 14);

	load_text();
}

void RectTextTest::update(float dt){
	if(view_){
		view_->Update(dt);
//		text_small_->Update(dt);
//		text_caps_->Update(dt);
//		text_nums_->Update(dt);
//		text_sp_->Update(dt);
	}
}
void RectTextTest::render(){
	if(view_){
		view_->Render();
//		text_small_->Render();
//		text_caps_->Render();
//		text_nums_->Render();
//		text_sp_->Render();
	}
}

void RectTextTest::load_text(){
	if(view_){
		unload_text();
	}
	//Draw a text
	assert(shader_);
	assert(font_);
	//factory_ = new he::TextViewFactory(shader_, new he::Font(he::ResourcePath() + "Courier New.ttf", 14));
	
				
	text_caps_ = new he::Text(shader_, font_, "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");
	text_small_ = new he::Text(shader_, font_, "the quick brown fox jumps over the lazy dog");
	text_nums_ = new he::Text(shader_, font_, "0123456789");
	text_sp_ =  new he::Text(shader_, font_, "~!@#$%^&*()_+-={}\\|;:'\"<>?,./");

	view_ = new he::View(he::Transform_Create(GLKVector2Make(0.0f, 0.0f)));
	view_->MoveSubview(new he::TextView(he::Transform_Create(GLKVector3Make(0.0f, -50.0f, 0.0f)), text_caps_, GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 1.0f)));
	view_->MoveSubview(new he::TextView(he::Transform_Create(GLKVector3Make(0.0f, 0.0f, 0.0f)), text_small_, GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 1.0f)));
	view_->MoveSubview(new he::TextView(he::Transform_Create(GLKVector3Make(0.0f, 50.0f, 0.0f)), text_nums_, GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 1.0f)));
	view_->MoveSubview(new he::TextView(he::Transform_Create(GLKVector3Make(0.0f, 100.0f, 0.0f)), text_sp_, GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 1.0f)));
	view_->MoveSubview(new AnimatedTextView(he::Transform_Create(GLKVector3Make(0.0f, -150.0f, 0.0f)), shader_, font_, "the quick brown fox jumps over the lazy dog", GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 1.0f)));
//	factory_->CreateTextView(he::Transform_Create(GLKVector3Make(0.0f, -50.0f, he::g_Screen->z_)), "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");
//	text_small_ = factory_->CreateTextView(he::Transform_Create(GLKVector3Make(0.0f, 0.0f, he::g_Screen->z_)), "the quick brown fox jumps over the lazy dog");
//	text_nums_ = factory_->CreateTextView(he::Transform_Create(GLKVector3Make(0.0f, 50.0f, he::g_Screen->z_)), "0123456789");
//	text_sp_ = factory_->CreateTextView(he::Transform_Create(GLKVector3Make(0.0f, 100.0f, he::g_Screen->z_)), "~!@#$%^&*()_+-={}\\|;:'\"<>?,./");
}

void RectTextTest::unload_text(){
	delete view_; view_ = 0;
	delete text_small_; text_small_ = 0;
	delete text_caps_; text_caps_ = 0;
	delete text_nums_; text_nums_ = 0;
	delete text_sp_; text_sp_ = 0;
}

void RectTextTest::HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ == he::Gesture::kTap && gesture.state_ == he::Gesture::kEnd){
		load_text();
	}
}


AnimatedTextView::AnimatedTextView(const he::Transform &transform, he::TextShader *shader, he::Font *font,
								   const std::string &string, GLKVector4 color) :
he::View(transform),
string_(string),
clock_(0.0f),
length_(0),
txt_vw_(nullptr),
color_(color)
{
	text_ = new he::Text(shader, font, "");
	update_string();
}

AnimatedTextView::~AnimatedTextView() {
	delete text_;
}

void AnimatedTextView::update_string() {
	length_++;
	if (length_ > string_.length()) {
		length_ = 0;
	}
	text_->SetString(string_.substr(0, length_));
	if (txt_vw_) {
		this->RemoveSubview(txt_vw_);
	}
	txt_vw_ = static_cast<he::TextView*>(this->MoveSubview(new he::TextView(he::Transform_Create(GLKVector3Make(0.0f, 0.0f, 0.0f)), text_, color_)));
}

void AnimatedTextView::Update(float dt) {
	clock_ += dt;
	if (clock_ > 0.3f) {
		clock_ = 0.0f;
		update_string();
	}
	he::View::Update(dt);
}
void AnimatedTextView::Render() {
	he::View::Render();
}

GLKVector2 AnimatedTextView::GetSize() const {
	return text_->GetSize();
}
//EOF