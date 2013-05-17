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

#include "AnimationStateData.h"
 

namespace spine {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ToEntry
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	AnimationStateData::ToEntry::ToEntry (Animation* to, float duration)  :
	animation_(to),
	duration_(duration),
	next_(0)
	{		}
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: FromEntry
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	AnimationStateData::FromEntry::FromEntry (Animation* from) :
	animation_(from),
	toEntries_(0),
	next_(0)
	{		}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: AnimationStateData
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	AnimationStateData::AnimationStateData (SkeletonData* skeletonData)  :
	skeletonData_(skeletonData),
	entries_(0)
	{	}
	
	AnimationStateData::~AnimationStateData () {
		ToEntry* toEntry;
		ToEntry* nextToEntry;
		FromEntry* nextFromEntry;
		
		FromEntry* fromEntry = (FromEntry*)entries_;
		while (fromEntry) {
			toEntry = fromEntry->toEntries_;
			while (toEntry) {
				nextToEntry = toEntry->next_;
				delete toEntry;
				toEntry = nextToEntry;
			}
			nextFromEntry = fromEntry->next_;
			delete fromEntry;
			fromEntry = nextFromEntry;
		}
	}
	
	void AnimationStateData::SetMixByName ( std::string fromName, std::string toName, float duration) {
		Animation* to;
		Animation* from = skeletonData_->FindAnimation( fromName);
		if (!from) return;
		to = skeletonData_->FindAnimation( toName);
		if (!to) return;
		AnimationStateData::SetMix( from, to, duration);
	}
	
	void AnimationStateData::SetMix ( Animation* from, Animation* to, float duration) {
		/* Find existing FromEntry. */
		ToEntry* toEntry;
		FromEntry* fromEntry = (FromEntry*)entries_;
		while (fromEntry) {
			if (fromEntry->animation_ == from) {
				/* Find existing ToEntry. */
				toEntry = fromEntry->toEntries_;
				while (toEntry) {
					if (toEntry->animation_ == to) {
						toEntry->duration_ = duration;
						return;
					}
					toEntry = toEntry->next_;
				}
				break; /* Add new ToEntry to the existing FromEntry. */
			}
			fromEntry = fromEntry->next_;
		}
		if (!fromEntry) {
			fromEntry = new FromEntry(from);
			fromEntry->next_ = (FromEntry*)entries_;
			entries_ = fromEntry;
		}
		toEntry = new ToEntry(to, duration);
		toEntry->next_ = fromEntry->toEntries_;
		fromEntry->toEntries_ = toEntry;
	}
	
	float AnimationStateData::GetMix ( Animation* from, Animation* to) {
		FromEntry* fromEntry = (FromEntry*)entries_;
		while (fromEntry) {
			if (fromEntry->animation_ == from) {
				ToEntry* toEntry = fromEntry->toEntries_;
				while (toEntry) {
					if (toEntry->animation_ == to) return toEntry->duration_;
					toEntry = toEntry->next_;
				}
			}
			fromEntry = fromEntry->next_;
		}
		return 0;
	}
	
	SkeletonData *AnimationStateData::GetSkeletonData(){
		return skeletonData_;
	}
}
