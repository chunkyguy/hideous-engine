//
//  Animation.cpp
//  HideousGameEngine
//
//  Created by Sid on 01/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Animation/Animation.h>
#include <he/Animation/AnimationLoop.h>
#include <he/Animation/easing.h>
#include <he/Utils/DebugLog.h>

namespace he{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Animation
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 Base class for Animation.
	 */
	Animation::~Animation(){
		if(state_ == kNaturalDeath){
			if(child_){
				//	Check for child's premature death. Could have been called Die() even before this moment arrived.
				if(child_->Done()){
					child_->Die(); delete child_; child_ = nullptr;
				}else{
					// From this moment on child is responsibilty of the AnimationLoop.
					g_AnimationLoop->MoveAndRunAnimation(child_);
				}
			}
			if(listener_){		// callback
				listener_->PerformAction(id_);
			}
		}else if(state_ == kSuicide && child_){
			child_->Die(); delete child_; child_ = nullptr;
		}
		//		FILE_LOG(logDEBUG) << "~Animation: (" << this << "|" << id_ << "|" << descent_id_ << ") " << (state_ == kNaturalDeath ? "Natural Death" : "Suicide" );
	}
	
	Animation::Animation() :
	id_(++uid),
	descent_id_(++d_uid),
	next_(nullptr),
	child_(nullptr),
	listener_(nullptr),
	state_(kPaused)
	{
		//		FILE_LOG(logDEBUG) << "Animation: (" << this << "|" << id_ << "|" << descent_id_ << ")";
	}
	
	//	Here are the steps that happens in order:
	//	1. update it self untill runs out of frames.
	//	2. If any listener is registered, call it.
	//	3. If has any child animation update it.
	void Animation::Update(float dt){
		if(state_ == kRunning){
			update(dt);
		}
	}
	
	//	Registers a child, to be executed after it finished.
	//	Owns it.
	Animation *Animation::MoveChild(Animation *child){
		child_ = child;
		for(Animation *child = child_; child; child = child->child_){
			child->descent_id_ = descent_id_;
		}
		return child;
	}
	
	//	Registers a listener. Calls it as soon as the animation finishes (before the child gets active)
	void Animation::SetListener(AnimationListenable *listener){
		listener_ = listener;
	}
	
	Animation::ID Animation::GetID() const{
		return id_;
	}
	
	Animation::ID Animation::GetDescentID() const{
		return descent_id_;
	}
	
	bool Animation::Done() const{
		return (state_ == kNaturalDeath) || (state_ == kSuicide);
	}
	
	void Animation::Die(){
		state_ = kSuicide;
	}

	void Animation::Pause() {
		assert(!Done());		// Error: Issuing command to a dead animation.
		state_ = kPaused;
	}
	void Animation::Run() {
		assert(!Done());		// Error: Issuing command to a dead animation.
		state_ = kRunning;
	}
	Animation::ID Animation::uid = 0ULL;
	Animation::ID Animation::d_uid = 0ULL;
	
}
///EOF
