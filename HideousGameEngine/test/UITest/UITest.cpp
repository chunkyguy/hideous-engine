//
//  UITest.cpp
//  HideousGameEngine
//
//  Created by Sid on 26/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "UITest.h"

#include <he/Animation/Animation.h>
#include <he/Font/Font.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/RectColorSh/RectColorSh.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Utils.h>
#include <he/Utils/Transform.h>
#include <he/Vertex/VertexCol.h>

#include "Label.h"

UITest::~UITest(){
//	if(scale_animation_){
//		delete scale_animation_; scale_animation_ = 0;
//	}
	delete render_object_;
	delete vertex_data_;
	delete shader_;
	delete label_;
	delete font_;
	he::g_EventLoop->RemoveListener(gesture_listener_);
	delete gesture_listener_;

	he::GlobalsDestroy();
}

UITest::UITest(double w, double h)
//:scale_animation_(0)
{
	//setup globals
	he::GlobalsInit(w, h);
	
	//debugger
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "Logging Enabled: " << loglevel << std::endl;
	FILE_LOG(logDEBUG) <<"{" <<w << "," << h << "}";

	//random
	srand(time(NULL));

	gesture_listener_ = new he::GestureListener<UITest>(this, &UITest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listener_);
	
	//start things here
	font_ = new he::Font("Silom.ttf", 34);
	label_ = new Label("Sid the best", font_);
	label_->transform_.SetPosition(GLKVector2Make(10, 20));

	shader_ = new he::RectColorSh;
	
	vertex_data_ = new he::VertexCol(0,0);
	vertex_data_->position_data_ = label_->GetBox().position_data_;
	GLKMatrix4 tMat = GLKMatrix4MakeTranslation(0, 0, -0.5);
	GLKMatrix4 mvpMat = GLKMatrix4Multiply(he::g_Screen->projection_, tMat);
	render_object_ = new he::RenderObject(vertex_data_, shader_, 0, mvpMat, GLKVector4Make(0.6, 0.8, 0.0, 0.5));
}

void UITest::Update(double dt){
//	if(scale_animation_){
//		if(!scale_animation_->NextFrame()){
//			delete scale_animation_; scale_animation_ = 0;
//			label_->SetColor(GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 1.0));
//		}
//	}
}
void UITest::Render(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	render_object_->Render();
	label_->Render();
}

void UITest::HandleGesture(const he::Gesture &gesture){
//	if(scale_animation_){	// block gestures while animating
//		return;
//	}
	
	if(gesture.action_ != he::Gesture::kTap){
		return;
	}
	
	GLKVector2 pt = gesture.GetHitPoint();
	if(label_->GetBox().position_data_.Contains(pt.x, pt.y)){
//		scale_animation_ = new he::AnimationChain;
//
//		GLKVector2 scaleUp = GLKVector2MultiplyScalar(label_->transform_.scale_, 1.25);
//		GLKVector2 scale_up_points[2] = {label_->transform_.scale_, scaleUp};
//		scale_animation_->Push(new he::Animation<GLKVector2>(&label_->transform_.scale_, he::MakeTweenFrames(3, he::kLinear, scale_up_points)));
//		
//		GLKVector2 scale_down_points[2] = {scaleUp, label_->transform_.scale_};
//		scale_animation_->Push(new he::Animation<GLKVector2>(&label_->transform_.scale_, he::MakeTweenFrames(3, he::kLinear, scale_down_points)));
	}else{
		label_->transform_.position_ = pt;
	}
}

///EOF
