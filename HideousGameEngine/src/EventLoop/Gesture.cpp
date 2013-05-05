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
	// MARK: Gesture
	Gesture g_Gesture;
	
	Gesture::Gesture(){
		Reset();
	}
	
	void Gesture::Reset(){
		fingers_ = 0;
		taps_ = 0;
		action_ = kNone;
		continious_ = false;
		touch_point_ = GLKVector2Make(0,0);
		velocity_ = GLKVector2Make(kDefaultMoveSpeed,kDefaultMoveSpeed);
	}
	
	GLKVector2 Gesture::GetHitPoint(){
		return CGtoGL(g_Gesture.touch_point_);
	}
}
//EOF