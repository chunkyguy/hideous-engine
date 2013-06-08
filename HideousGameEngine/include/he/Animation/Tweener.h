//
//  Tweener.h
//  HideousGameEngine
//
//  Created by Sid on 22/05/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_Tweener_h
#define HideousGameEngine_Tweener_h

#include <he/Animation/easing.h>

namespace he{
	
	//	Provides value between two end points.
	//	Any class that provides following operations is tweenable:
	//	1. Addition:								operator + ()
	//	2. Subtraction:							operator - ()
	//	3. Multiplication with floating type:		operator * (const float)
	//	4. Copyable (for returning)				copy constructor | operator = ()
	
	template<typename T>
	class Tweener{
	public:
		Tweener(EasingFunction func, T start, T end) :
		function_(func),
		start_(start),
		end_(end)
		{		}
		
		//	time := [0, 1] always.
		//	So at time = 0, returned value is start
		//	And at time = 1, returned value is end
		T operator()(float time){
			return start_ + function_(time) * (end_ - start_);
		}
		
	private:
		T start_;
		T end_;

		//	fucntion pointer taking in a floating type, and returning a floating type.
		EasingFunction function_;
	};
}
#endif
