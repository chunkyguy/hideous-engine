/*******************************************************************************
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#ifndef SPINE_ANIMATIONSTATE_H_
#define SPINE_ANIMATIONSTATE_H_

#include "AnimationStateData.h"

namespace spine {
	
	class AnimationState{
	public:
		/* @param data May be 0 for no mixing. */
		explicit AnimationState(AnimationStateData* data);
		~AnimationState();
		
		void Update ( float delta);
		
		void Apply ( Skeleton* skeleton);
		
		/* @param animationName May be 0. */
		void SetAnimationByName (std::string animationName, bool loop);
		/* @param animation May be 0. */
		void SetAnimation ( Animation* animation, bool loop);
		
		/** @param animationName May be 0.
		 * @param delay May be <= 0 to use duration of previous animation minus any mix duration plus the negative delay. */
		void AddAnimationByName ( std::string animationName, bool loop, float delay);
		/** @param animation May be 0.
		 * @param delay May be <= 0 to use duration of previous animation minus any mix duration plus the negative delay. */
		void AddAnimation ( Animation* animation, bool loop, float delay);
		
		void ClearAnimation ();
		
		bool IsComplete ();
		
	private:
		
		void set_animation ( Animation* newAnimation, bool loop);
		void clear_queue();
		
		struct Internal{
			Internal();
			
			struct Entry {
				Entry();
				
				Animation* animation;
				float delay;
				bool loop;
				Entry* next;
			};
			
			bool previousLoop;
			float mixDuration;
			float mixTime;
			Animation *previous;
			float previousTime;
			Entry* queue;
		} ;
		
		Internal *internal_;
		AnimationStateData *data_;
		Animation *animation_;
		float time_;
		bool loop_;
	} ;
}

#endif /* SPINE_ANIMATIONSTATE_H_ */
