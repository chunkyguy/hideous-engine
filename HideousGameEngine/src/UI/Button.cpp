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
	View(frame.GetTransform()),
	listner_(listner),
	gesture_listener_(nullptr),
	tag_(tag),
	frame_(frame)
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
	
	GLKVector2 ButtonView::GetSize() const {
		return frame_.GetSize();
	}
	
	void ButtonView::HandleGesture(const he::Gesture &gesture){
		if(gesture.action_ == he::Gesture::kTap && gesture.state_ == he::Gesture::kEnd){
			GLKVector2 point = gesture.GetHitPoint();
			GLKVector2 size = frame_.GetSize();
			GLKVector4 center = GLKMatrix4GetColumn(Transform_GetMV(&transform_), 3);
			if (point.x > center.x-(size.x/2.0f) &&
				point.x < center.x+(size.x/2.0f) &&
				point.y > center.y-(size.y/2.0f) &&
				point.y < center.y+(size.y/2.0f)) {
				he_Trace("ButtonView: A %d, hit\n",tag_);
				listner_->Hit(this);
			}

//			if(he::Vertex::Contains(frame_.GetGlobalRect(), point)){
//				he_Trace("ButtonView: B %d, hit\n",tag_);
//				//listner_->Hit(this);
//			}
		}
	}
	
	int ButtonView::GetTag() const{
		return tag_;
	}
	

} /*namespace he*/

///EOF
