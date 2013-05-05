//
//  Animation.cpp
//  HideousGameEngine
//
//  Created by Sid on 01/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Animation/Animation.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tweens
/////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace{
	double Linear(double a, double b, double t){
		return a + (b-a)*t;
	}
	
	double EaseIn(double a, double b, double t){
		return a + (b-a) * t * t;
	}
	
	double EaseOut(double a, double b, double t){
		return a - (b-a)*t*(t-2);
	}
	
	double EaseInOut(double a, double b, double t){
		t *= 2;
		if(t<=1.0){return a + (b-a)/2 * t * t;}
		t -= 1;
		return a - (b-a)/2*(t*(t-2)-1);
	}
	
	double EaseOutCubic(double a, double b, double t){
		t -= 1;
		return a + (b-a)*(t*t*t+1);
	}
}

namespace he{

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// TweenFrame Utils
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	TweenFrame<GLKVector2> *MakeTweenFrame2D(int steps ,GLKVector2 start, GLKVector2 end, TweenFrame<GLKVector2>::Type animType){
		
//	GLKVector2 dPos = GLKVector2Make((end.x - start.x)/(steps-1), (end.y - start.y)/(steps-1));
//		FILE_LOG(logDEBUG) << "start: " << "{" << start.x << "," << start.y << "}";
//		FILE_LOG(logDEBUG) << "end: " << "{" << end.x << "," << end.y << "}";
//		FILE_LOG(logDEBUG) << "dPos: " << "{" << dPos.x << "," << dPos.y << "}";
		
		GLKVector2 *tween = new GLKVector2[steps];
		int s = 0;
		double t = 0.0;
		for(double dt = 1.0/(double)(steps-1); s < steps-1; s++){
			switch(animType){
				case TweenFrame<GLKVector2>::kLinear:		//a + (b-a)*t;
					tween[s] = GLKVector2Make(Linear(start.x, end.x, t), Linear(start.y, end.y, t));
					break;
					
				case TweenFrame<GLKVector2>::kEaseIn:		//a + (b-a) * t * t;
					tween[s] = GLKVector2Make(EaseIn(start.x, end.x, t), EaseIn(start.y, end.y, t));
					break;
					
				case TweenFrame<GLKVector2>::kEaseOut:	//a - (b-a)*t*(t-2);
					tween[s] = GLKVector2Make(EaseOut(start.x, end.x, t), EaseOut(start.y, end.y, t));
					break;
					
				case TweenFrame<GLKVector2>::kEaseInOut:	//t *= 2; if(t<=1.0){return a + (b-a)/2 * t * t;} t -= 1; return a - (b-a)/2*(t*(t-2)-1);
					tween[s] = GLKVector2Make(EaseInOut(start.x, end.x, t), EaseInOut(start.y, end.y, t));
					break;
					
				case TweenFrame<GLKVector2>::kEaseOutCubic:	//t -= 1; return a + (b-a)*(t*t*t+1);
					tween[s] = GLKVector2Make(EaseOutCubic(start.x, end.x, t), EaseOutCubic(start.y, end.y, t));
					break;
			}
			t += dt;
			//			FILE_LOG(logDEBUG) << "tween: [" << s << "]: " << "{" << tween[s].x << "," << tween[s].y << "}";
		}
		tween[s] = end;
		//		FILE_LOG(logDEBUG) << "tween: [" << s << "]: " << "{" << tween[s].x << "," << tween[s].y << "}";
		return new TweenFrame<GLKVector2>(steps, tween);
	}

	
	TweenFrame<double> *MakeTweenFrame1D(int steps ,double start, double end, TweenFrame<double>::Type animType){
		
		//		double dRot = (end - start)/(steps-1);
		
//		FILE_LOG(logDEBUG) << "start: " << "{" << start << "}";
//		FILE_LOG(logDEBUG) << "end: " << "{" << end << "}";
//		FILE_LOG(logDEBUG) << "dPos: " << "{" << dRot << "}";
		
		double *tween = new double[steps];
		int s = 0;
		double t = 0.0;
		for(double dt = 1.0/(double)(steps-1); s < steps-1; s++){
			switch(animType){
				case TweenFrame<double>::kLinear:		//a + (b-a)*t;
					tween[s] = Linear(start, end, t);
					break;
					
				case TweenFrame<double>::kEaseIn:		//a + (b-a) * t * t;
					tween[s] = Linear(start, end, t);
					break;
					
				case TweenFrame<double>::kEaseOut:	//a - (b-a)*t*(t-2);
					tween[s] = Linear(start, end, t);
					break;
					
				case TweenFrame<double>::kEaseInOut:	//t *= 2; if(t<=1.0){return a + (b-a)/2 * t * t;} t -= 1; return a - (b-a)/2*(t*(t-2)-1);
					tween[s] = Linear(start, end, t);
					break;
					
				case TweenFrame<double>::kEaseOutCubic:	//t -= 1; return a + (b-a)*(t*t*t+1);
					tween[s] = Linear(start, end, t);
					break;
			}
			t += dt;
			//			FILE_LOG(logDEBUG) << "tween: [" << s << "]: " << "{" << tween[s] << "}";
		}
		tween[s] = end;
		//		FILE_LOG(logDEBUG) << "tween: [" << s << "]: " << "{" << tween[s] << "}";
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
