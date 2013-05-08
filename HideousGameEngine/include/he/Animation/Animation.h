//
//  Animation.h
//  HideousGameEngine
//
//  Created by Sid on 01/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__Animation__
#define __HideousGameEngine__Animation__
#include <GLKit/GLKMath.h>

#include <deque>

#include "DebugLog.h"

namespace he{
	
	//	All class have a
	//	bool NextFrame();
	//	Check for and delete.
	//	Every object deletes the objects it holds.
	//	TweenFrame -> all objects.
	//	Animation -> TweenFrame
	//	AnimationChain -> Animation
	
	typedef enum{
		kLinear,
		
		kQuadraticEaseIn,
		kQuadraticEaseOut,
		kQuadraticEaseInOut,
		
		kCubicEaseIn,
		kCubicEaseOut,
		kCubicEaseInOut,
		
		kQuarticEaseIn,
		kQuarticEaseOut,
		kQuarticEaseInOut,
		
		kQuinticEaseIn,
		kQuinticEaseOut,
		kQuinticEaseInOut,
		
		kSineEaseIn,
		kSineEaseOut,
		kSineEaseInOut,
		
		kCircularEaseIn,
		kCircularEaseOut,
		kCircularEaseInOut,
		
		kExponentialEaseIn,
		kExponentialEaseOut,
		kExponentialEaseInOut,
		
		kElasticEaseIn,
		kElasticEaseOut,
		kElasticEaseInOut,
		
		kBackEaseIn,
		kBackEaseOut,
		kBackEaseInOut,
		
		kBounceEaseIn,
		kBounceEaseOut,
		kBounceEaseInOut,
		
	}EasingFunction;

	
	// Generate tweens between two end points with selected algorithm.
	template <typename T>
	class TweenFrame {
	public:
		TweenFrame(int steps, T *tweens) :
		container_(tweens),
		container_size_(steps),
		step_(0)
		{		}
		
		~TweenFrame(){
			if(container_){
				delete [] container_;
				container_ = 0;
			}
		}
		
		
		bool NextFrame(T &value){
			if(step_ >= container_size_){
				return false;
			}
			
			value = container_[step_];
			step_++;
			return true;
		}
		
		
	private:
		T *container_;
		int container_size_;
		int step_;
	};
	
	
	// Helper factory methods to create TweenFrames for 1D and 2D
	//	Don't own the objects.
	TweenFrame<GLKVector2> *MakeTweenFrames(int steps, EasingFunction easing_func, GLKVector2 end_point[2]);
	TweenFrame<double> *MakeTweenFrames(int steps, EasingFunction easing_func, double end_point[2]);
	
	//	Base class for every animatable object
	class IAnimatable{
	public:
		virtual ~IAnimatable(){}
		virtual bool NextFrame() = 0;
	};
	 
	//	Binds the TweenFrame's object with the client's object
	template<typename T>
	class Animation : public IAnimatable{
	public:
		Animation(T *v, TweenFrame<T> *a) :
		anim_(a),
		value_(v)
		{}
		
		~Animation(){
			delete anim_;
			anim_ = nullptr;
		}
		
		bool NextFrame(){
			return anim_->NextFrame(*value_);
		}
		
	private:
		TweenFrame<T> *anim_;
		T *value_;
	};
	
	//	Collection of more than one Animation. All run back to back in order they're pushed.
	class AnimationChain{
	public:
		AnimationChain();
		~AnimationChain();
		void Push(IAnimatable *a);
		bool NextFrame();
		
	private:
		IAnimatable *current_frame_;
		std::deque<IAnimatable *> frames_;
	};
	
}
#endif /* defined(__HideousGameEngine__Animation__) */
