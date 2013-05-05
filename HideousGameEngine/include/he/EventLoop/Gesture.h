//
//  Gesture.h
//  SCML
//
//  Created by Sid on 25/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__Gesture__
#define __HideousGameEngine__Gesture__
#include <GLKit/GLKMath.h>

namespace he{
	class Gesture{
	public:
		Gesture();
		void Reset();
		GLKVector2 GetHitPoint();	// In OpenGL coord space

		typedef enum{
			kTap,
			kZoomIn,
			kZoomOut,
			kDrag,
			kNone
		}Action;
		Action action_;
		
		typedef enum{
			kBegin,
			kChange,
			kEnd,
			kCancel,
			kFail,
			kPossible
		}State;
		State state_;
		
		int fingers_;
		int taps_;
		bool continious_;
		GLKVector2 touch_point_;	// In UIKit coord space
		GLKVector2 velocity_;
		
	private:
		const float kDefaultMoveSpeed = 2.0; //units per second
	};
	
	extern Gesture g_Gesture;	
}
#endif /* defined(__HideousGameEngine__Gesture__) */
