//
//  Animation.cpp
//  HideousGameEngine
//
//  Created by Sid on 01/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Animation/Animation.h>
#include <he/Animation/easing.h>
#include <he/Utils/DebugLog.h>

namespace he{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Animatable
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 Base class for Animation.
	 */
	Animatable::~Animatable(){
		if(state_ == kNaturalDeath){
			if(child_){
				//	Check for child's premature death. Could have been called Die() even before this moment arrived.
				if(child_->Done()){
					child_->Die(); delete child_; child_ = nullptr;
				}else{
					// From this moment on child is responsibilty of the AnimationLoop.
					g_AnimationLoop->AddAnimation(child_);
				}
			}
			if(listener_){		// callback
				listener_->PerformAction(id_);
			}
		}else if(state_ == kSuicide && child_){
			child_->Die(); delete child_; child_ = nullptr;
		}
		//		FILE_LOG(logDEBUG) << "~Animatable: (" << this << "|" << id_ << "|" << descent_id_ << ") " << (state_ == kNaturalDeath ? "Natural Death" : "Suicide" );
	}
	
	Animatable::Animatable() :
	id_(++uid),
	descent_id_(++d_uid),
	next_(nullptr),
	child_(nullptr),
	listener_(nullptr),
	state_(kAlive)
	{
		//		FILE_LOG(logDEBUG) << "Animatable: (" << this << "|" << id_ << "|" << descent_id_ << ")";
	}
	
	//	Here are the steps that happens in order:
	//	1. update it self untill runs out of frames.
	//	2. If any listener is registered, call it.
	//	3. If has any child animation update it.
	void Animatable::Update(float dt){
		if(state_ == kAlive){
			update(dt);
		}
	}
	
	//	Registers a child, to be executed after it finished.
	//	Owns it.
	void Animatable::AddChild(Animatable *child){
		child_ = child;
		for(Animatable *child = child_; child; child = child->child_){
			child->descent_id_ = descent_id_;
		}
		//		FILE_LOG(logDEBUG) << "Animatable: (" << this << "|" << id_ << "|" << descent_id_ << ") -> child(" << child_ << "|" << child_->id_ << "|" << child_->descent_id_ << ")";
	}
	
	//	Registers a listener. Calls it as soon as the animation finishes (before the child gets active)
	void Animatable::SetListener(AnimationListenable *listener){
		listener_ = listener;
	}
	
	unsigned long Animatable::GetID() const{
		return id_;
	}
	
	unsigned long Animatable::GetDescentID() const{
		return descent_id_;
	}
	
	bool Animatable::Done() const{
		return state_ != kAlive;
	}
	
	void Animatable::Die(){
		state_ = kSuicide;
	}
	
	unsigned long Animatable::uid = 0UL;
	unsigned long Animatable::d_uid = 0UL;
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
			Animatable *p = head_;
			Animatable *q = p->next_;
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
		
		for (Animatable *a = head_; a; a = a->next_) {
			a->Update(dt);
		}
	}
	
	void AnimationLoop::AddAnimation( Animatable *a){
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
		Animatable *p = nullptr;
		Animatable *q = head_;
		while(q){
			Animatable *del = nullptr;
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
		for(Animatable *p = head_; p; p = p->next_){
			FILE_LOG(logDEBUG) << "(" << p << "|" << p->GetID() << "|" << p->GetDescentID() << ")";
		}
		FILE_LOG(logDEBUG) << "]";
	}
	
	AnimationLoop *g_AnimationLoop = nullptr;
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Helpers
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	EndAnimationFunctor::EndAnimationFunctor(IDType type, unsigned long ID) :
	id_(ID),
	type_(type)
	{}
	
	void EndAnimationFunctor::operator()(he::Animatable *animation){
		unsigned long ID = (type_ == kAnimationID) ? animation->GetID(): animation->GetDescentID();
		if(ID == id_){
			animation->Die();
		}
	}	
	
	void EndAnimationsWithID(EndAnimationFunctor::IDType type, unsigned long ID){
		he::g_AnimationLoop->TraverseAnimations(EndAnimationFunctor(type, ID));
	}
	
	/*
	 /////////////////////////////////////////////////////////////////////////////////////////////////////////
	 // TweenFrame Utils
	 /////////////////////////////////////////////////////////////////////////////////////////////////////////
	 easing::AHEasingFunction type_to_function(EasingFunction easing_func){
	 he::easing::AHEasingFunction function = nullptr;
	 switch(easing_func){
	 case kLinear: function = easing::LinearInterpolation; break;
	 
	 case kQuadraticEaseIn: function = easing::QuadraticEaseIn; break;
	 case	 kQuadraticEaseOut: function = easing::QuadraticEaseOut; break;
	 case	 kQuadraticEaseInOut: function = easing::QuadraticEaseInOut; break;
	 
	 case	 kCubicEaseIn: function = easing::CubicEaseIn;break;
	 case	 kCubicEaseOut: function = easing::CubicEaseOut;break;
	 case kCubicEaseInOut: function = easing::CubicEaseInOut; break;
	 
	 case	 kQuarticEaseIn: function = easing::QuarticEaseIn; break;
	 case	 kQuarticEaseOut: function = easing::QuarticEaseOut; break;
	 case	 kQuarticEaseInOut: function = easing::QuarticEaseInOut; break;
	 
	 case kQuinticEaseIn: function = easing::QuinticEaseIn;break;
	 case kQuinticEaseOut: function = easing::QuinticEaseOut;break;
	 case kQuinticEaseInOut: function = easing::QuinticEaseInOut;break;
	 
	 case kSineEaseIn: function = easing::SineEaseIn;break;
	 case kSineEaseOut: function = easing::SineEaseOut;break;
	 case kSineEaseInOut: function = easing::SineEaseInOut;break;
	 
	 case kCircularEaseIn: function = easing::CircularEaseIn;break;
	 case kCircularEaseOut: function = easing::CircularEaseOut; break;
	 case kCircularEaseInOut: function = easing::CircularEaseInOut; break;
	 
	 case kExponentialEaseIn: function = easing::ExponentialEaseIn;break;
	 case kExponentialEaseOut: function = easing::ExponentialEaseOut; break;
	 case kExponentialEaseInOut: function = easing::ExponentialEaseInOut; break;
	 
	 case kElasticEaseIn: function = easing::ElasticEaseIn; break;
	 case kElasticEaseOut: function = easing::ElasticEaseOut; break;
	 case kElasticEaseInOut: function = easing::ElasticEaseInOut; break;
	 
	 case kBackEaseIn: function = easing::BackEaseIn;break;
	 case kBackEaseOut: function = easing::BackEaseOut; break;
	 case kBackEaseInOut: function = easing::BackEaseInOut; break;
	 
	 case kBounceEaseIn: function = easing::BounceEaseIn; break;
	 case kBounceEaseOut: function = easing::BounceEaseOut; break;
	 case kBounceEaseInOut: function = easing::BounceEaseInOut; break;
	 }
	 
	 return function;
	 }
	 
	 TweenFrame<GLKVector2> *MakeTweenFrames(int steps, EasingFunction easing_func, GLKVector2 end_point[2]){
	 
	 FILE_LOG(logDEBUG) << "start: " << "{" << end_point[0].x << "," << end_point[0].y << "}";
	 FILE_LOG(logDEBUG) << "end: " << "{" << end_point[1].x << "," << end_point[1].y << "}";
	 FILE_LOG(logDEBUG) << "steps: " << steps;
	 
	 he::easing::AHEasingFunction function = type_to_function(easing_func);
	 GLKVector2 *tween = new GLKVector2[steps];
	 float t = 0.0;
	 float dt = 1.0 / (steps - 1);
	 for(int frame = 0; frame < steps; ++frame, t += dt)	{
	 float x = end_point[0].x + function(t) * (end_point[1].x - end_point[0].x);
	 float y = end_point[0].y + function(t) * (end_point[1].y - end_point[0].y);
	 FILE_LOG(logDEBUG) << "at:[" << frame << "]: {" << x << "," << y << "}";
	 tween[frame] = GLKVector2Make(x,y);
	 }
	 
	 return new TweenFrame<GLKVector2>(steps, tween);
	 }
	 
	 
	 TweenFrame<float> *MakeTweenFrames(int steps, EasingFunction easing_func, float end_point[2]){
	 
	 //		float dRot = (end - start)/(steps-1);
	 
	 //		FILE_LOG(logDEBUG) << "start: " << "{" << start << "}";
	 //		FILE_LOG(logDEBUG) << "end: " << "{" << end << "}";
	 //		FILE_LOG(logDEBUG) << "dPos: " << "{" << dRot << "}";
	 he::easing::AHEasingFunction function = type_to_function(easing_func);
	 float *tween = new float[steps];
	 float t = 0.0;
	 float dt = 1.0 / (steps - 1);
	 for(int frame = 0; frame < steps; ++frame, t += dt)	{
	 tween[frame] = end_point[0] + function(t) * (end_point[1] - end_point[0]);
	 }
	 
	 return new TweenFrame<float>(steps, tween);
	 }
	 
	 /////////////////////////////////////////////////////////////////////////////////////////////////////////
	 // AnimationChain
	 /////////////////////////////////////////////////////////////////////////////////////////////////////////
	 AnimationChain::~AnimationChain(){
	 while(!frames_.empty()){
	 delete frames_.front();
	 frames_.pop_front();
	 }
	 frames_.clear();
	 }
	 AnimationChain::AnimationChain() :
	 current_frame_(0)
	 {}
	 void AnimationChain::Push(IAnimatable *a){
	 frames_.push_back(a);
	 }
	 bool AnimationChain::NextFrame(){
	 if(frames_.empty()){
	 return false;
	 }
	 
	 if(!current_frame_){
	 current_frame_ = frames_.front();
	 }
	 
	 if(!current_frame_->NextFrame()){
	 delete current_frame_;
	 current_frame_ = 0;
	 frames_.pop_front();
	 }
	 return true;
	 }
	 */
}
///EOF
