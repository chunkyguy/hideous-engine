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

#ifndef SPINE_SKELETONDATA_H_
#define SPINE_SKELETONDATA_H_

#include "BoneData.h"
#include "SlotData.h"
#include "Skin.h"
#include "SpineAnimation.h"


namespace spine {
	
	class SkeletonData {
	public:
		SkeletonData (int bones, int slots, int skins, int animations);
		~SkeletonData ();
				
		BoneData* FindBone ( std::string boneName) const;
		int FindBoneIndex ( std::string boneName) const;
		SlotData* FindSlot ( std::string slotName) const;
		int FindSlotIndex ( std::string slotName) const;
		Skin* FindSkin ( std::string skinName) const;
		spine::Animation* FindAnimation ( std::string animationName) const;
		
		Skin* GetDefaultSkin();

		int GetBoneCount();
		BoneData *GetBoneDataAtIndex(int index);
		void PushBone( BoneData *data);

		int GetSlotCount();
		SlotData *GetSlotDataAtIndex(int index);
		void PushSlot( SlotData *data);
		
		int GetSkinCount();
		void PushSkin( Skin *data);
		
		int GetAnimationCount();
		Animation *GetAnimationAtIndex(int index);
		void PushAnimation(Animation *anim);
			
	private:
		int boneCount_;
		BoneData** bones_;
		
		int slotCount_;
		SlotData** slots_;
		
		int skinCount_;
		Skin** skins_;
		Skin* defaultSkin_;
		
		int animationCount_;
		Animation** animations_;
	};
	
	
}

#endif /* SPINE_SKELETONDATA_H_ */
