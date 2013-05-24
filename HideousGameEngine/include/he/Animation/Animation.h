//
//  Animation.h
//  HideousGameEngine
//
//  Created by Sid on 01/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__Animation__
#define __HideousGameEngine__Animation__
#include <he/Utils/GLKMath_Additions.h>

#include <deque>

#include <he/Animation/Tweener.h>
#include <he/Utils/DebugLog.h>

namespace he{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: AnimationListenable
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
		Protocol for AnimationListener
	 */
	struct AnimationListenable{
		virtual ~AnimationListenable(){}
		virtual void PerformAction(int animation_id) = 0;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: AnimationListener
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 Generic AnimationListener
	 */
	template <typename T>
	class AnimationListener : public AnimationListenable{
	public:
		typedef void(T::*callback)(int animation_id);
		AnimationListener(T *object, callback method) :
		object_(object),
		method_(method)
		{}

		// Calls the registered callback.
		void PerformAction(int animation_id){
			(object_->*method_)(animation_id);
		}
		
	private:
		T *object_;			// The object.
		callback method_;	// The method.
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Animatable
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
		Base class for Animation.
	 */
	class Animatable{
	public:
		Animatable();

		// This could happen under two circumstances:
		//	1. Natural Death:
		//	Adds child (if any) to the animation loop and calls the callback.
		//	Assuming that the callback isn't going to refer to this animation anymore directly or indirectly.
		//	2. Suicide:
		//	Forcibly kills the child (and subsquently the whole family tree) without calling the registered callback (if any)
		virtual ~Animatable();
		
		//	Nothing to do here, invokes updates on derived class.
		//	The derived class then updates till it runs out of frames,
		//	in that case the AnimationLoop kills it naturally.
		void Update(double dt);
		
		//	Registers a child, to be executed after self is finished.
		//	Owns it.
		void AddChild(Animatable *child);
		
		//	Registers a listener. Calls it as soon as the animation finishes (after the child gets active)
		void SetListener(AnimationListenable *listener);
		
		//	All id are > 0
		//	Get the animation id associated.
		unsigned long GetID() const;
		
		//	Get associated descent id. All parent-child share same descent id.
		unsigned long GetDescentID() const;
		
		//	Done = true, means the animation doesn't wants to live anymore (natural death or suicide)
		//	Used by AnimationLoop to kick out of the loop.
		bool Done() const;

		//	Commits suicide.
		//	Anyone is free to call this anytime.
		//	Doesn't means that memory will be released immediately. It just sets a flag, kicked out of loop by AnimationLoop
		void Die();
		
		//	Never expected to be used from any place else other than the AnimationLoop.
		//	Points to the next sibling.
		Animatable *next_;
		//	Points to the next child in waiting.
		Animatable *child_;

	protected:
		typedef enum{kAlive, kNaturalDeath, kSuicide} State;

		State state_;
		
	private:

		virtual void update(double dt) = 0;

		unsigned long id_;
		unsigned long descent_id_;
		AnimationListenable *listener_;
		
		//	The id's are generated from 1 to sizeof(unsigned long). Someday if someone plays for too long, the game will crash.
		// TODO: Fix this sometime in future.
		static unsigned long uid;
		static unsigned long d_uid;
	};
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Animation
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
		Generic Animation class.
		Rule #1: Any object for which a Tweener can be created can be animated.
	 */
	template<typename T>
	class Animation : public Animatable{
	public:
		~Animation(){
			delete [] frames_;
		}
		
		Animation(T *value, Tweener<T> tweener, int frames, double delay = 0.0) :
		value_(value),
		frames_(new T [frames]),
		frame_count_(frames),
		active_frame_(-1),
		clock_(0.0),
		delay_(delay)
		{
			// Here is a sample of how these values looks like:
			//	Lets say, frames = 5.
			//	dt = 1/4
			//	t[5] = { 0, 1/4, 1/2, 3/4, 1 }
			double t = 0.0;
			double dt = 1.0 / (frames - 1);
			for(int frame = 0; frame < frames; ++frame, t += dt)	{
				frames_[frame] = tweener(t);
			}
		}
		
		
	private:
		void update(double dt){
			clock_ += dt;
			if(clock_ > delay_){
				if(active_frame_ + 1 >= frame_count_){
					state_ = kNaturalDeath;
				}else{
					*value_ = frames_[++active_frame_];
					clock_ = 0.0;
				}
			}
		}
		
		T *value_;				// The value during animation. Provided by the tweener.
		T *frames_;				// Holds all frames required for animation.
		int frame_count_;		// Total number of frames in the animation sequence.
		int active_frame_;		// Index of the frame executing.
		double clock_;			// Clock resets after each frame execution. Relevant only when using delay.
		double delay_;			// Delay between each frame.
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: AnimationLoop
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 Start if from some good place and add/remove animations at runtime. If not active, no animation is going to run.
	 This is the heart of all animations.
	 Owns all added animations.
	 */
	class AnimationLoop{
	public:
		AnimationLoop();
		
		// Removes any pending animation with suicide
		~AnimationLoop();
		
		// Add an animation in a seperate linked list. List is merged with the main list at next update.
		void AddAnimation(Animatable *a);
		
		//	Simple way to traverse all animation.
		//	Needs a function pointer, functor, whatever as argument.
		template<typename FUNC>
		void TraverseAnimations(FUNC func){
			for(Animatable *p = head_; p; p = p->next_){
				func(p);
			}
		}
		
		// Need to be called only from a single place. Best the root class, that updates everything.
		void Update(double dt);
		
	private:
		// Actual merging of new animations to the main list.
		void add_animations();
		
		// Removes unwanted animations from the loop. Assumes the animation is in the loop.
		void remove_animations();

		//	for debugging.
		void print_list();
		
		//	The main head pointer of the linked list.
		Animatable *head_;
		
		//	Head and tail of the temporary linked list, where every new animation gets added.
		Animatable *new_head_;
		Animatable *new_tail_;
	};

	// Call the he/Utils/Utils.h => GlobalsCreate() at init stage of the game to create this
	extern AnimationLoop *g_AnimationLoop;
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Helpers
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	Committing suicide at destructors is such a common task, that we have a helper for it.
	//	Can be called in two ways, depending on whether it's a single animation or a animation family.
	class EndAnimationFunctor {
	public:
		typedef enum {kAnimationID, kDescentID} IDType;
		EndAnimationFunctor(IDType type, unsigned long ID);
		void operator()(he::Animatable *animation);
		
	private:
		unsigned long id_;
		IDType type_;
	};
	void EndAnimationsWithID(EndAnimationFunctor::IDType type, unsigned long ID);
}
#endif /* defined(__HideousGameEngine__Animation__) */
