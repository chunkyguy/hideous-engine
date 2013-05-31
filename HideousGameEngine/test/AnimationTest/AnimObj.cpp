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
	end_animations();
	delete render_object_;
	delete vert_data_;
	if(animation_listener_){
		delete animation_listener_;
	}
}

AnimObj::AnimObj( int ID, he::RectColorSh *shader ) :
id_(ID),
transform_(GLKVector2Make(0.0, 0.0), 0.0, GLKVector2Make(1.0, 1.0)),
//tmp_transform_(0),
//anim_chain_(0)
shader_(shader),
animation_listener_(nullptr),
scale_anim_descent_id_(0UL),
trans_anim_descent_id_(0UL)
{
	vert_data_ = new he::VertexCol(-50.0, 50.0);
	GLKVector4 color = GLKVector4Make(0.0, 0.0, 0.0, 1.0);
	render_object_ = new he::RenderObject(vert_data_, shader_, 0, he::g_Screen->projection_, color);
	animation_listener_ = new he::AnimationListener<AnimObj>(this, &AnimObj::AnimationCallback);
}

void AnimObj::Update(double dt){
	
	// Get MV-matrix from transform or tmpTransform.
	//	GLKMatrix4 mvMat = transform_.GetMV();;
	/*
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
	 */
	render_object_->SetMVP(transform_.GetMVP());
}

#pragma mark - Animations
void AnimObj::TouchEnd(GLKVector2 pt){
	FILE_LOG(logDEBUG) << "TouchEnd (" << id_ << ")";
	end_animations();
	
	GLKVector2 scale_points[2] = {transform_.scale_, GLKVector2MultiplyScalar(transform_.scale_, 2.0)};
	he::Animation<GLKVector2> *scale_animation = new he::Animation<GLKVector2>(&transform_.scale_,
																			   he::Tweener<GLKVector2>(he::BackEaseIn, scale_points[0], scale_points[1]),
																			   100);
	he::Animation<GLKVector2> *scale_down_anim = new he::Animation<GLKVector2>(&transform_.scale_,
																			   he::Tweener<GLKVector2>(he::BounceEaseOut, scale_points[1], scale_points[0]),
																			   50);
	GLKVector4 rand_color = GLKVector4Make(he::Randf(),he::Randf(),he::Randf(),1.0);
	he::Animation<GLKVector4> *color_switch = new he::Animation<GLKVector4>(&render_object_->color_,
																			he::Tweener<GLKVector4>(he::Linear, render_object_->color_, rand_color),
																			100);
	color_switch->SetListener(animation_listener_);
	scale_down_anim->AddChild(color_switch);
	scale_animation->AddChild(scale_down_anim);
	he::g_AnimationLoop->AddAnimation(scale_animation);
	scale_anim_descent_id_ = scale_animation->GetDescentID();
	
	he::Animation<GLKVector2> *trans_animation = new he::Animation<GLKVector2>(&transform_.position_,
																			   he::Tweener<GLKVector2>(he::Linear, transform_.position_, pt),
																			   100);
	trans_animation->AddChild(new he::Animation<double>(&transform_.rotation_,
														he::Tweener<double>(he::Linear, transform_.rotation_, atan2(pt.y, pt.x)),
														80));
	he::g_AnimationLoop->AddAnimation(trans_animation);
	trans_anim_descent_id_ = trans_animation->GetDescentID();
	
	/*
	 if(anim_chain_){
	 delete anim_chain_; anim_chain_ = 0;
	 delete tmp_transform_; tmp_transform_ = 0;
	 }
	 
	 tmp_transform_ = new he::Transform(transform_);
	 anim_chain_ = new he::AnimationChain;
	 
	 GLKVector2 scale_up_points[2] = {tmp_transform_->scale_, GLKVector2MultiplyScalar(tmp_transform_->scale_, 1.2)};
	 anim_chain_->Push( new he::Animation<GLKVector2>(&tmp_transform_->scale_, he::MakeTweenFrames(30, he::kElasticEaseIn, scale_up_points)));
	 
	 GLKVector2 trans_points[2] = {tmp_transform_->position_, pt};
	 anim_chain_->Push(new he::Animation<GLKVector2>(&tmp_transform_->position_, he::MakeTweenFrames(60, he::kBounceEaseOut, trans_points)));
	 
	 GLKVector2 scale_down_points[2] = {GLKVector2MultiplyScalar(tmp_transform_->scale_, 1.2), tmp_transform_->scale_};
	 anim_chain_->Push(new he::Animation<GLKVector2>(&tmp_transform_->scale_, he::MakeTweenFrames(30, he::kElasticEaseOut, scale_down_points)));
	 
	 double rotation_points[2] = {tmp_transform_->rotation_, atan2(pt.y, pt.x)};
	 anim_chain_->Push(new he::Animation<double>(&tmp_transform_->rotation_, he::MakeTweenFrames(20, he::kLinear, rotation_points)));
	 */
}

struct end_anim {
	end_anim(unsigned long des_id) : des_id_(des_id)	{}
	
	void operator()(he::Animatable *animation){
		if(animation->GetDescentID() == des_id_){
			animation->Die();
		}
	}
	unsigned long des_id_;
};

void AnimObj::end_animations(){
	
	he::g_AnimationLoop->TraverseAnimations(end_anim(scale_anim_descent_id_));
	he::g_AnimationLoop->TraverseAnimations(end_anim(trans_anim_descent_id_));
}

void AnimObj::Render(){
	render_object_->Render();
}

void AnimObj::AnimationCallback(int animation_id){
	transform_ = he::Transform(GLKVector2Make(0.0, 0.0), 0.0, GLKVector2Make(1.0, 1.0));
	render_object_->SetColor( GLKVector4Make(0.0, 0.0, 0.0, 1.0) );
}
///EOF
