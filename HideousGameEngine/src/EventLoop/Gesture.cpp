//
//  Gesture.cpp
//  SCML
//
//  Created by Sid on 25/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/EventLoop/Gesture.h>
#include <he/Utils/Screen.h>
#include <he/Utils/Utils.h>
#include <he/Utils/DebugLog.h>

namespace he{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Gesture
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	Gesture::Gesture() :
	fingers_(0),
	taps_(0),
	action_(kNone),
	continious_(false),
	touch_point_(GLKVector2Make(0,0)),
	velocity_(GLKVector2Make(kDefaultMoveSpeed,kDefaultMoveSpeed))
	{}
	
	GLKVector2 Gesture::GetHitPoint() const{
		return CGtoGL(touch_point_);
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: EventLoop
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EventLoop *g_EventLoop = nullptr;
	
	EventLoop::EventLoop() :
	head_(nullptr)
	{}
	
	void EventLoop::AddListener(GestureListenable *listener){
		if(!head_){
			head_ = listener;
		}else{
			listener->next_ = head_;
			head_ = listener;
		}
	}
	
	void EventLoop::RemoveListener(GestureListenable *listener){
		if(listener == head_){
			head_ = listener->next_;
		}else{
			GestureListenable *gl = head_;
			for(; gl->next_ != listener; gl = gl->next_)
				;
			gl->next_ = listener->next_;
		}
	}
	
	void EventLoop::SetGesture(const Gesture &gesture){
		for(GestureListenable *gl = head_; gl; gl = gl->next_){
			gl->PerformAction(gesture);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: GestureListenable
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	GestureListenable::GestureListenable() :
	next_(nullptr)
	{}
	
	GestureListenable::~GestureListenable(){
	}

}
//EOF