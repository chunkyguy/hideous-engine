//
//  Animation.cpp
//  HideousGameEngine
//
//  Created by Sid on 01/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Animation/Animation.h>
#include <he/Animation/easing.h>

namespace he{
	
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
		double t = 0.0;
		double dt = 1.0 / (steps - 1);
		for(int frame = 0; frame < steps; ++frame, t += dt)	{
			double x = end_point[0].x + function(t) * (end_point[1].x - end_point[0].x);
			double y = end_point[0].y + function(t) * (end_point[1].y - end_point[0].y);
			FILE_LOG(logDEBUG) << "at:[" << frame << "]: {" << x << "," << y << "}";
			tween[frame] = GLKVector2Make(x,y);
		}
		
		return new TweenFrame<GLKVector2>(steps, tween);
	}
	
	
	TweenFrame<double> *MakeTweenFrames(int steps, EasingFunction easing_func, double end_point[2]){
		
		//		double dRot = (end - start)/(steps-1);
		
		//		FILE_LOG(logDEBUG) << "start: " << "{" << start << "}";
		//		FILE_LOG(logDEBUG) << "end: " << "{" << end << "}";
		//		FILE_LOG(logDEBUG) << "dPos: " << "{" << dRot << "}";
		he::easing::AHEasingFunction function = type_to_function(easing_func);
		double *tween = new double[steps];
		double t = 0.0;
		double dt = 1.0 / (steps - 1);
		for(int frame = 0; frame < steps; ++frame, t += dt)	{
			tween[frame] = end_point[0] + function(t) * (end_point[1] - end_point[0]);
		}
		
		return new TweenFrame<double>(steps, tween);
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
	
}
///EOF
