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
	// MARK: Animation
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
		Base class for Animation.
	 */
	class Animation{
	public:
		typedef unsigned long long ID;
		/**
		 *	Create blank animation with default state
		 */
		Animation();
		
		/**
		 *	Destroy animation.
		 *
		 *	@brief This could happen under two circumstances:
		 *	1. Natural Death:
		 *	Adds child (if any) to the animation loop and calls the callback.
		 *	Assuming that the callback isn't going to refer to this animation anymore directly or indirectly.
		 *	2. Suicide:
		 *	Forcibly kills the child (and subsquently the whole family tree) without calling the registered callback (if any)
		 */
		virtual ~Animation();
		
		/**
		 *	Update
		 *
		 *	@brief	Nothing to do here, invokes updates on derived class.
		 *	The derived class then updates till it runs out of frames,
		 *	in that case the AnimationLoop kills it naturally.
		 *
		 *	@param	dt	delta time.
		 */
		void Update(float dt);
		
		/**
		 *	Registers a child, to be executed after self is finished. Owns it.
		 *
		 *	@param	child	The child animation.
		 */
		void MoveChild(Animation *child);
		
		/**
		 *	Registers a listener. Calls it as soon as the animation finishes (after the child gets active)
		 *
		 *	@param	listener		The listener.
		 */
		void SetListener(AnimationListenable *listener);
		
		/**
		 *	Get the animation id associated.
		 *
		 *	@note		All id are > 0
		 *
		 *	@return	The unique animation ID.
		 */
		ID GetID() const;
		
		/**
		 *	Get associated descent id. All parent-child share same descent id.
		 *
		 *	@return	The unique descent id.
		 */
		ID GetDescentID() const;
		
		/**
		 *	Done = true, means the animation doesn't wants to live anymore (natural death or suicide)
		 *
		 *	@brief		Used by AnimationLoop to kick out of the loop.
		 *
		 *	@return	True is still active, else false.
		 */
		bool Done() const;

		/**
		 *	Commits suicide.
		 *
		 *	@brief	Anyone is free to call this anytime.
		 *	Doesn't means that memory will be released immediately. It just sets a flag, kicked out of loop by AnimationLoop
		 */
		void Die();
		
		/**
		 *	Never expected to be used from any place else other than the AnimationLoop.
		 *	Points to the next sibling.
		 */
		Animation *next_;
		
		/**
		 *	Points to the next child in waiting.
		 */
		Animation *child_;

	protected:
		typedef enum{kAlive, kNaturalDeath, kSuicide} State;

		State state_;
		
	private:

		virtual void update(float dt) = 0;

		ID id_;
		ID descent_id_;
		AnimationListenable *listener_;
		
		//	The id's are generated from 1 to sizeof(unsigned long). Someday if someone plays for too long, the game will crash.
		// TODO: Fix this sometime in future.
		static ID uid;
		static ID d_uid;
	};
	
	
}
#endif /* defined(__HideousGameEngine__Animation__) */
