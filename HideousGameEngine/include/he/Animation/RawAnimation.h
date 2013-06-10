//
//  RawAnimation.h
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_RawAnimation_h
#define HideousGameEngine_RawAnimation_h

#include <he/Animation/Animation.h>

namespace he{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Animation
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 Generic Animation class.
	 Rule #1: Any object for which a Tweener can be created can be animated.
	 */
	template<typename T>
	class RawAnimation : public Animation{
	public:
		~RawAnimation(){
			delete [] frames_;
		}
		
		RawAnimation(T *value, Tweener<T> tweener, int frames, float fps = 24.0f) :
		value_(value),
		frames_(new T [frames]),
		frame_count_(frames),
		active_frame_(-1),
		clock_(0.0f),
		delay_(1.0f/fps)
		{
			// Here is a sample of how these values looks like:
			//	Lets say, frames = 5.
			//	dt = 1/4
			//	t[5] = { 0, 1/4, 1/2, 3/4, 1 }
			float t = 0.0f;
			float dt = 1.0f / (frames - 1);
			for(int frame = 0; frame < frames; ++frame, t += dt)	{
				frames_[frame] = tweener(t);
			}
		}
		
		
	private:
		void update(float dt){
			clock_ += dt;
			if(clock_ > delay_){
				if(active_frame_ + 1 >= frame_count_){
					state_ = kNaturalDeath;
				}else{
					*value_ = frames_[++active_frame_];
					clock_ = 0.0f;
				}
			}
		}
		
		T *value_;				// The value during animation. Provided by the tweener.
		T *frames_;				// Holds all frames required for animation.
		int frame_count_;		// Total number of frames in the animation sequence.
		int active_frame_;		// Index of the frame executing.
		float clock_;			// Clock resets after each frame execution. Relevant only when using delay.
		float delay_;			// Delay between each frame.
	};
	
}
#endif
