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

#ifndef SPINE_ANIMATIONSTATEDATA_H_
#define SPINE_ANIMATIONSTATEDATA_H_

#include "SpineAnimation.h"
#include "SkeletonData.h"

namespace spine {
	
	class AnimationStateData {
	public:
		explicit AnimationStateData (SkeletonData* skeletonData);
		~AnimationStateData();
		
		void SetMixByName ( std::string fromName, std::string toName, float duration);
		void SetMix ( spine::Animation* from, spine::Animation* to, float duration);
		/* Returns 0 if there is no mixing between the animations. */
		float GetMix (spine::Animation* from, spine::Animation* to);
		SkeletonData *GetSkeletonData();
		
	private:
		class ToEntry {
		public:
			ToEntry (Animation* to, float duration);
			
			Animation* animation_;
			float duration_;
			ToEntry* next_;
		};

		class FromEntry {
		public:
			FromEntry (Animation* from);
			
			Animation* animation_;
			ToEntry* toEntries_;
			FromEntry* next_;
		};

		SkeletonData *skeletonData_;
		void *entries_;
	} ;
}
#endif /* SPINE_ANIMATIONSTATEDATA_H_ */