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
#include <he/Utils/DebugHelper.h>

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
	
	std::ostream &operator<<(std::ostream &os, const Gesture &g){
		std::string action = "";
		switch (g.action_) {
			case Gesture::kTap: action = "Tap"; break;
			case Gesture::kZoomIn: action = "ZoomIn"; break;
			case Gesture::kZoomOut: action = "ZoomOut"; break;
			case Gesture::kDrag: action = "Drag"; break;
			case Gesture::kNone:
			default: action = "UNKNOWN"; break;
		}
		std::string state = "";
		switch (g.state_) {
			case Gesture::kBegin: state =  "Begin"; break;
			case Gesture::kChange: state = "Change"; break;
			case Gesture::kEnd: state = "End"; break;
			case Gesture::kCancel: state = "Cancel"; break;
			case Gesture::kFail: state = "Fail"; break;
			case Gesture::kPossible: state = "Possible"; break;
			default: state = "UNKNOWN"; break;
		}

		he_Trace("Action: %@\n"
				 "Continous: %@\n"
				 "Fingers: %@\n"
				 "State: %@\n"
				 "Taps: %@\n"
				 "TouchPoint(UI coord space): %@\n"
				 "HitPoint(GL coord space): %@\n"
				 "Velocity: %@",
				 action, (g.continious_?"Y":"N"), g.fingers_, state, g.taps_, g.touch_point_, g.GetHitPoint(), g.velocity_);

		return os;
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