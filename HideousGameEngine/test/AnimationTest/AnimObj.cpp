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
#include <he/Animation/RawAnimation.h>
#include <he/Animation/AnimationLoop.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/ColorShader.h>
#include <he/Vertex/ColorVertex.h>

AnimObj::~AnimObj(){
	end_animations();
	delete render_object_;
	delete vert_data_;
	if(animation_listener_){
		delete animation_listener_;
	}
}

AnimObj::AnimObj( int ID, he::ColorShader *shader ) :
id_(ID),
//tmp_transform_(0),
//anim_chain_(0)
shader_(shader),
animation_listener_(nullptr),
scale_anim_descent_id_(0UL), 
trans_anim_descent_id_(0UL)
{
	transform_ = he::Transform_Create(GLKVector2Make(0.0f, 0.0f), GLKVector4Make(0, 0, 1, 0));
	float dimension = 100.0f;
	he::ColorVertex::Data min = {GLKVector2Make(-dimension/2.0f, -dimension/2.0f), GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 0.7f)};
	he::ColorVertex::Data max = {GLKVector2Make(dimension/2.0f, dimension/2.0f), GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 0.7f)};
	
	vert_data_ = new he::ColorVertex(min, max);
	GLKVector4 color = GLKVector4Make(0.0, 0.0, 0.0, 1.0);
	render_object_ = new he::RenderObject(vert_data_, shader_, 0, he::g_Screen->projection_, color);
	animation_listener_ = new he::AnimationListener<AnimObj>(this, &AnimObj::AnimationCallback);
}

void AnimObj::Update(float dt){
	
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
	render_object_->SetMVP(he::Transform_GetMVP(&transform_));
}

#pragma mark - Animations
void AnimObj::TouchEnd(GLKVector2 pt){
	FILE_LOG(logDEBUG) << "TouchEnd (" << id_ << ")";
	end_animations();
	
	GLKVector3 scale_points[2] = {transform_.scale, transform_.scale * 1.2f};
	he::RawAnimation<GLKVector3> *scale_animation = new he::RawAnimation<GLKVector3>(&(transform_.scale),
																			   he::Tweener<GLKVector3>(he::BackEaseIn, scale_points[0], scale_points[1]),
																			   25);
	he::RawAnimation<GLKVector3> *scale_down_anim = new he::RawAnimation<GLKVector3>(&(transform_.scale),
																					 he::Tweener<GLKVector3>(he::BounceEaseOut, scale_points[1], scale_points[0]),
																					 25);
	scale_animation->MoveChild(scale_down_anim);
	scale_down_anim->SetListener(animation_listener_);
//	GLKVector4 rand_color = GLKVector4Make(he::Randf(),he::Randf(),he::Randf(),1.0);
//	he::RawAnimation<GLKVector4> *color_switch = new he::RawAnimation<GLKVector4>(&render_object_->color_,
//																			he::Tweener<GLKVector4>(he::Linear, render_object_->color_, rand_color),
//																			35);
//	color_switch->SetListener(animation_listener_);
//	scale_down_anim->AddChild(color_switch);
//	scale_animation->AddChild(scale_down_anim);

	he::g_AnimationLoop->MoveAnimation(scale_animation);
	scale_anim_descent_id_ = scale_animation->GetDescentID();

	he::RawAnimation<GLKVector3> *trans_animation = new he::RawAnimation<GLKVector3>(&(transform_.position),
																					 he::Tweener<GLKVector3>(he::Linear, transform_.position, GLKVector3Make(pt.x, pt.y, transform_.position.z)),
																					 30);
	he::RawAnimation<float> *rot_anim = new he::RawAnimation<float>(&(transform_.rotation.w),
																	he::Tweener<float>(he::Linear, transform_.rotation.w, GLKMathDegreesToRadians(45.0f)),
																	10);
	trans_animation->MoveChild(rot_anim);
	he::g_AnimationLoop->MoveAnimation(trans_animation);
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
	 
	 float rotation_points[2] = {tmp_transform_->rotation_, atan2(pt.y, pt.x)};
	 anim_chain_->Push(new he::Animation<float>(&tmp_transform_->rotation_, he::MakeTweenFrames(20, he::kLinear, rotation_points)));
	 */
}

struct end_anim {
	end_anim(he::Animation::ID des_id) : des_id_(des_id)	{}
	
	void operator()(he::Animation *animation){
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

void AnimObj::AnimationCallback(he::Animation::ID animation_id){
	transform_ = he::Transform_Create(GLKVector2Make(0.0f, 0.0f));
	render_object_->SetColor( GLKVector4Make(0.0, 0.0, 0.0, 1.0) );
}
///EOF
