//
//  AnimationLoop.h
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_AnimationLoop_h
#define HideousGameEngine_AnimationLoop_h

#include <he/Animation/Animation.h>

namespace he {
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: AnimationLoop
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 Start if from some good place and add/remove animations at runtime. 
	 If not active, no animation is going to run.
	 This is the heart of all animations.
	 Owns all added animations.
	 */
	class AnimationLoop{
	public:
		AnimationLoop();
		
		/**
		 *	Removes any pending animation with suicide
		 */
		~AnimationLoop();

		/**
		 *	Add an animation in a seperate linked list. List is merged with the main list at next update.
		 *	Remember every animation is in paused state by default, so it's caller's responsiblity to call Run() on the animation.
		 *
		 *	@param	a	animation object.
		 *
		 *	@return	animation object, can be used for chaining.
		 */
		Animation* MoveAnimation(Animation *a);

		/**
		 *	Adds animation to the loop and starts running immediately
		 *	Add an animation in a seperate linked list. List is merged with the main list at next update.
		 *	Call animation->Run().
		 *
		 *	@param	a	animation object.
		 *
		 *	@return	animation object, can be used for chaining.
		 */
		Animation *MoveAndRunAnimation(Animation *a);
		
		/**
		 *	Simple way to traverse all animation.
		 *	Needs a function pointer, functor, whatever as argument.
		 */
		template<typename FUNC>
		void TraverseAnimations(FUNC func){
			for(Animation *p = head_; p; p = p->next_){
				func(p);
			}
		}
		
		/**
		 *	Need to be called only from a single place. Best the root class, that updates everything.
		 *
		 *	@param	dt	Delta time in seconds.
		 */
		void Update(float dt);
		
	private:
		/**
		 *	Actual merging of new animations to the main list.
		 */
		void add_animations();
		
		/**
		 *	Removes unwanted animations from the loop. Assumes the animation is in the loop.
		 */
		void remove_animations();
		
		/**
		 *	for debugging.
		 */
		void print_list();
		
		/**
		 *	The main head pointer of the linked list.
		 */
		Animation *head_;
		
		/**
		 *	Head and tail of the temporary linked list, where every new animation gets added.
		 */
		Animation *new_head_;
		Animation *new_tail_;
	};
	
	/**
	 *	Call the he/Utils/Utils.h => GlobalsCreate() at init stage of the game to create this
	 */
	extern AnimationLoop *g_AnimationLoop;
	
}

#endif
