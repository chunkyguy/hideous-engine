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

#include "AnimationState.h"

namespace spine {
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: AnimationState
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	AnimationState::AnimationState (AnimationStateData* data)  :
	data_(data),
	animation_(0),
	time_(0),
	loop_(false),
	internal_(new Internal)
	{	}
	
	void AnimationState::clear_queue () {
		Internal::Entry* entry = internal_->queue;
		while (entry) {
			Internal::Entry* nextEntry = entry->next;
			delete entry;
			entry = nextEntry;
		}
		internal_->queue = 0;
	}
	
	AnimationState::~AnimationState () {
		clear_queue();
		delete internal_;
	}
	
#include <stdio.h>
	
	void AnimationState::AddAnimation ( Animation* animation, bool loop, float delay) {
		Internal::Entry* existingEntry;
		Animation* previousAnimation;
		
		Internal::Entry* entry = new Internal::Entry;
		entry->animation = animation;
		entry->loop = loop;
		
		existingEntry = internal_->queue;
		if (existingEntry) {
			while (existingEntry->next)
				existingEntry = existingEntry->next;
			existingEntry->next = entry;
			previousAnimation = existingEntry->animation;
		} else {
			internal_->queue = entry;
			previousAnimation = animation_;
		}
		
		if (delay <= 0) {
			if (previousAnimation)
				delay = previousAnimation->GetDuration() - data_->GetMix( previousAnimation, animation) + delay;
			else
				delay = 0;
		}
		entry->delay = delay;
	}
	
	void AnimationState::AddAnimationByName ( std::string animationName, bool loop, float delay) {
		Animation* animation = data_->GetSkeletonData()->FindAnimation( animationName);
		if(animation){
			AddAnimation( animation, loop, delay);
		}
	}
	
	void AnimationState::set_animation ( Animation* newAnimation, bool loop) {
		internal_->previous = 0;
		if (newAnimation && animation_ && data_) {
			internal_->mixDuration = data_->GetMix( animation_, newAnimation);
			if (internal_->mixDuration > 0) {
				internal_->mixTime = 0;
				internal_->previous = animation_;
				internal_->previousTime = time_;
				internal_->previousLoop = loop_;
			}
		}
		animation_ = newAnimation;
		loop_ = loop;
		time_ = 0;
	}
	
	void AnimationState::SetAnimation ( Animation* newAnimation, bool loop) {
		clear_queue();
		set_animation( newAnimation, loop);
	}
	
	void AnimationState::SetAnimationByName (std::string animationName, bool loop) {
		Animation* animation = data_->GetSkeletonData()->FindAnimation( animationName);
		if(animation){
			SetAnimation( animation, loop);
		}
	}
	
	void AnimationState::ClearAnimation () {
		internal_->previous = 0;
		animation_ = 0;
		clear_queue();
	}
	
	void AnimationState::Update ( float delta) {
		Internal::Entry* next;
		
		time_ += delta;
		internal_->previousTime += delta;
		internal_->mixTime += delta;
		
		if (internal_->queue && time_ >= internal_->queue->delay) {
			set_animation(internal_->queue->animation, internal_->queue->loop);
			next = internal_->queue->next;
			delete internal_->queue;
			internal_->queue = next;
		}
	}
	
	void AnimationState::Apply ( Skeleton* skeleton) {
		float alpha;
		
		if (!animation_) return;
		if (internal_->previous) {
			internal_->previous->Apply( skeleton, internal_->previousTime, internal_->previousLoop);
			alpha = internal_->mixTime / internal_->mixDuration;
			if (alpha >= 1) {
				alpha = 1;
				internal_->previous = 0;
			}
			animation_->Mix( skeleton, time_, loop_, alpha);
		} else
			animation_->Apply( skeleton, time_, loop_);
	}
	
	bool AnimationState::IsComplete () {
		return !animation_ || time_ >= animation_->GetDuration();
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: AnimationState::Internal::Entry
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	AnimationState::Internal::Entry::Entry() :
	animation(nullptr),
	delay(0.0),
	loop(false),
	next(nullptr)
	{}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: AnimationState::Internal
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	AnimationState::Internal::Internal() :
	previousLoop(false),
	mixDuration(0.0),
	mixTime(0.0),
	previous(nullptr),
	previousTime(0.0),
	queue(nullptr)
	{}

}
