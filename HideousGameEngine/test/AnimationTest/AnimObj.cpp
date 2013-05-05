//
//  AnimObj.cpp
//  HideousGameEngine
//
//  Created by Sid on 01/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "AnimObj.h"

#include <he/Utils/DebugLog.h>
#include <he/Utils/Utils.h>
#include <he/Animation/Animation.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/RectColorSh/RectColorSh.h>
#include <he/Vertex/VertexCol.h>

AnimObj::~AnimObj(){
	if(anim_chain_){
		delete anim_chain_;	anim_chain_ = 0;
		delete tmp_transform_; tmp_transform_ = 0;
	}
	delete render_object_;
	delete shader_;
	delete vert_data_;
}

AnimObj::AnimObj() :
transform_(GLKVector2Make(0.0, 0.0), 0.0, GLKVector2Make(1.0, 1.0)),
tmp_transform_(0),
anim_chain_(0)
{
	shader_ = new he::RectColorSh;
	vert_data_ = new he::VertexCol(-50.0, 50.0);
	GLKVector4 color = GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), he::Randf());
	render_object_ = new he::RenderObject(vert_data_, shader_, 0, he::g_Screen.projection_, color);
}

void AnimObj::Update(double dt){

	// Get MV-matrix from transform or tmpTransform.
	GLKMatrix4 mvMat;

	//	Run animations if available.
	if(anim_chain_){
		if(!anim_chain_->NextFrame()){
			// animation done. save transform state.
			transform_ = *tmp_transform_;
			mvMat = transform_.GetMV();

			delete anim_chain_; anim_chain_ = 0;
			delete tmp_transform_; tmp_transform_ = 0;
		}else{
			mvMat = tmp_transform_->GetMV();
		}
	}else{
		mvMat = transform_.GetMV();
	}
	
	GLKMatrix4 mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, mvMat);
	render_object_->mvp_ = mvpMat;
}

#pragma mark - Animations
void AnimObj::TouchEnd(GLKVector2 pt){

	if(anim_chain_){
		delete anim_chain_; anim_chain_ = 0;
		delete tmp_transform_; tmp_transform_ = 0;
	}

	tmp_transform_ = new he::Transform(transform_);
	anim_chain_ = new he::AnimationChain;
	
	anim_chain_->Push(new he::Animation<GLKVector2>(&tmp_transform_->scale_, he::MakeTweenFrame2D(10, tmp_transform_->scale_, GLKVector2MultiplyScalar(tmp_transform_->scale_, 2.0), he::TweenFrame<GLKVector2>::kEaseOut)));
	anim_chain_->Push(new he::Animation<GLKVector2>(&tmp_transform_->scale_, he::MakeTweenFrame2D(10, GLKVector2MultiplyScalar(tmp_transform_->scale_, 2.0), tmp_transform_->scale_, he::TweenFrame<GLKVector2>::kEaseIn)));
	anim_chain_->Push(new he::Animation<GLKVector2>(&tmp_transform_->position_, he::MakeTweenFrame2D(10, tmp_transform_->position_, pt, he::TweenFrame<GLKVector2>::kEaseOutCubic)));
	anim_chain_->Push(new he::Animation<double>(&tmp_transform_->rotation_, he::MakeTweenFrame1D(10, tmp_transform_->rotation_, atan2(pt.y, pt.x), he::TweenFrame<double>::kEaseOutCubic)));
}

void AnimObj::Render(){
	render_object_->Render();
}
///EOF
