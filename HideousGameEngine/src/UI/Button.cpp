//
//  Button.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "Button.h"

#include <he/UI/ImageView.h>

namespace he {
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ButtonView
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ButtonView::ButtonView(const Frame &frame, IButtonListener *listner, int tag) :
	View(frame),
	listner_(listner),
	gesture_listener_(nullptr),
	tag_(tag)
	{
		// add gesture listener
		gesture_listener_ = new he::GestureListener<ButtonView>(this, &ButtonView::HandleGesture);
		he::g_EventLoop->AddListener(gesture_listener_);
	}

	ButtonView::~ButtonView() {
		he::g_EventLoop->RemoveListener(gesture_listener_);
		delete gesture_listener_;
	}
	
	void ButtonView::Update(float dt) {
		View::Update(dt);
	}
	
	void ButtonView::Render() {
		View::Render();
	}
	
	void ButtonView::HandleGesture(const he::Gesture &gesture){
		if(gesture.action_ == he::Gesture::kTap && gesture.state_ == he::Gesture::kEnd){
			GLKVector2 pt = gesture.GetHitPoint();
			if(he::Vertex::Contains(GetFrame().GetGlobalRect(), pt)){
				listner_->Hit(this);
			}
		}
	}
	
	int ButtonView::GetTag() const{
		return tag_;
	}
	

} /*namespace he*/

///EOF
