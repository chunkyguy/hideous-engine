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

#include "SkeletonData.h"
#include <string.h>
 


namespace spine {


	SkeletonData::SkeletonData (int bones, int slots, int skins, int animations) :
	bones_(new BoneData *[bones]),
	boneCount_(0),
	slots_(new SlotData *[slots]),
	slotCount_(0),
	skins_(new Skin *[skins]),
	skinCount_(0),
	animations_(new Animation *[animations]),
	animationCount_(0)
	{}
	
	SkeletonData::~SkeletonData () {
		int i;
		for (i = 0; i < boneCount_; ++i){
			delete bones_[i];
		}
		delete bones_;
		
		for (i = 0; i < slotCount_; ++i){
			delete slots_[i];
		}
		delete [] slots_;
		
		for (i = 0; i < skinCount_; ++i){
			delete skins_[i];
		}
		delete [] skins_;
		
		for (i = 0; i < animationCount_; ++i){
			delete animations_[i];
		}
		delete [] animations_;
	}
	
	BoneData* SkeletonData::FindBone ( std::string boneName) const{
		int i;
		for (i = 0; i < boneCount_; ++i){
			if (bones_[i]->GetName() == boneName){
				return bones_[i];
			}
		}
		return 0;
	}
	
	int SkeletonData::FindBoneIndex ( std::string boneName) const{
		int i;
		for (i = 0; i < boneCount_; ++i){
			if (bones_[i]->GetName() == boneName){
				return i;}
		}
		return 0;
	}
	
	SlotData* SkeletonData::FindSlot ( std::string slotName) const{
		int i;
		for (i = 0; i < slotCount_; ++i){
			if (slots_[i]->GetName() == slotName){
				return slots_[i];
			}
		}
		return 0;
	}
	
	int SkeletonData::FindSlotIndex ( std::string slotName) const{
		int i;
		for (i = 0; i < slotCount_; ++i){
			if (slots_[i]->GetName() == slotName) {
				return i;
			}
		}
		return 0;
	}
	
	Skin* SkeletonData::FindSkin ( std::string skinName) const{
		int i;
		for (i = 0; i < skinCount_; ++i){
			if (skins_[i]->GetName() == skinName){
				return skins_[i];
			}
		}
		return 0;
	}
	
	Animation* SkeletonData::FindAnimation ( std::string animationName) const{
		int i;
		for (i = 0; i < animationCount_; ++i){
			if (animations_[i]->GetName() == animationName){
				return animations_[i];
			}
		}
		return 0;
	}
	
	Skin* SkeletonData::GetDefaultSkin(){
		return defaultSkin_;
	}
	
	int SkeletonData::GetBoneCount(){
		return boneCount_;
	}
	BoneData *SkeletonData::GetBoneDataAtIndex(int index){
		return bones_[index];
	}
	void SkeletonData::PushBone( BoneData *data){
		bones_[boneCount_++] = data;
	}

	int SkeletonData::GetSlotCount(){
		return slotCount_;
	}
	SlotData *SkeletonData::GetSlotDataAtIndex(int index){
		return slots_[index];
	}
	void SkeletonData::PushSlot(SlotData *data){
		slots_[slotCount_++] = data;
	}

	int SkeletonData::GetSkinCount(){
		return skinCount_;
	}
	void SkeletonData::PushSkin(Skin *data){
		skins_[skinCount_++] = data;
		if (data->GetName() == "default"){
			defaultSkin_ = data;
		}

	}

	int SkeletonData::GetAnimationCount(){
		return animationCount_;
	}
	Animation *SkeletonData::GetAnimationAtIndex(int index){
		return animations_[index];
	}
	void SkeletonData::PushAnimation(Animation *anim){
		animations_[animationCount_++] = anim;
	}
}
