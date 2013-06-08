//
//  AnimationLoop.cpp
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Animation/AnimationLoop.h>


namespace he {
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: AnimationLoop
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 Start if from some good place and add/remove animations at runtime. If not active, no animation is going to run.
	 This is the heart of all animations.
	 */
	
	// Kill all the pending animations at the end of the day.
	AnimationLoop::~AnimationLoop(){
		if(head_){
			Animation *p = head_;
			Animation *q = p->next_;
			while(q) {
				p->Die(); delete p; p = nullptr;
				p = q;
				q = p->next_;
			}
			p->Die(); delete p; p = nullptr;
		}
	}
	
	AnimationLoop::AnimationLoop():
	head_(nullptr),
	new_head_(nullptr),
	new_tail_(nullptr)
	{}
	
	//	3 Steps:
	//	1 - Remove all zombie animations.
	//	2 - Merge all pending new animations.
	//	3 - Update all animations
	void AnimationLoop::Update(float dt){
		remove_animations();
		add_animations();
		
		for (Animation *a = head_; a; a = a->next_) {
			a->Update(dt);
		}
	}
	
	void AnimationLoop::AddAnimation( Animation *a){
		//FILE_LOG(logDEBUG) << "AnimationLoop: AddAnimation(" << a << "|" << a->GetID() << "|" << a->GetDescentID() << ")";
		if(!new_head_){
			new_tail_ = new_head_ = a;
		}else{
			a->next_ = new_head_;
			new_head_ = a;
		}
		//		FILE_LOG(logDEBUG) << "AnimationLoop: AddAnimation: " << a->GetID();
	}
	
	void AnimationLoop::add_animations(){
		if(new_tail_){
			assert(new_head_);
			new_tail_->next_ = head_;
			head_ = new_head_;
			
			new_head_ = new_tail_ = nullptr;
		}
	}
	
	void AnimationLoop::remove_animations(){
		Animation *p = nullptr;
		Animation *q = head_;
		while(q){
			Animation *del = nullptr;
			if(q->Done()){
				del = q;
				//FILE_LOG(logDEBUG) << "AnimationLoop: remove_animation(" << del << "|" << del->GetID() << "|" << del->GetDescentID() << ")";
				if(p){
					p->next_ = q->next_;
				}
			}else{
				p = q;
			}
			q = q->next_;
			if(del){
				if(del == head_){
					head_ = head_->next_;
				}
				delete del; del = nullptr;
			}
		}
	}
	
	void AnimationLoop::print_list(){
		FILE_LOG(logDEBUG) << "[";
		for(Animation *p = head_; p; p = p->next_){
			FILE_LOG(logDEBUG) << "(" << p << "|" << p->GetID() << "|" << p->GetDescentID() << ")";
		}
		FILE_LOG(logDEBUG) << "]";
	}
	
	AnimationLoop *g_AnimationLoop = nullptr;
	
}