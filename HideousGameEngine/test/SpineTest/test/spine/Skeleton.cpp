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

#include "Skeleton.h"
#include <string.h>
 

namespace spine {
	
	Skeleton::Skeleton (SkeletonData* data) {
		int i, ii;
		
		data_ = data;
		
		boneCount_ = data_->GetBoneCount();
		bones_ = new Bone* [boneCount_];
		
		for (i = 0; i < boneCount_; ++i) {
			BoneData* boneData = data_->GetBoneDataAtIndex(i);
			Bone* parent = 0;
			if (boneData->GetParent()) {
				/* Find parent bone. */
				for (ii = 0; ii < boneCount_; ++ii) {
					if (data->GetBoneDataAtIndex(ii) == boneData->GetParent()) {
						parent = bones_[ii];
						break;
					}
				}
			}
			bones_[i] = new Bone(boneData, parent);
		}
		root_ = bones_[0];
		
		slotCount_ = data->GetSlotCount();
		slots_ = new Slot* [slotCount_];
		for (i = 0; i < slotCount_; ++i) {
			SlotData *slotData = data->GetSlotDataAtIndex(i);
			
			/* Find bone for the slotData's boneData. */
			Bone *bone = nullptr;
			for (ii = 0; ii < boneCount_; ++ii) {
				if (data->GetBoneDataAtIndex(ii) == slotData->GetBoneData()) {
					bone = bones_[ii];
					break;
				}
			}
			
			slots_[i] = new Slot(slotData, this, bone);
		}
		
		drawOrder_ = new Slot* [slotCount_];
		memcpy(drawOrder_, slots_, sizeof(Slot*) * slotCount_);
		color_ = GLKVector4Make(1, 1, 1, 1);
	}
	
	Skeleton::~Skeleton () {
		int i;
		for (i = 0; i < boneCount_; ++i){
			delete bones_[i];
		}
		delete [] bones_;
		
		for (i = 0; i < slotCount_; ++i){
			delete slots_[i];
		}
		delete [] slots_;
		
		delete [] drawOrder_;
	}
	
	void Skeleton::UpdateWorldTransform () const {
		int i;
		for (i = 0; i < boneCount_; ++i)
			bones_[i]->UpdateWorldTransform( flipX_, flipY_);
	}
	
	void Skeleton::SetToSetupPose() const {
		SetBonesToSetupPose();
		SetSlotsToSetupPose();
	}
	
	void Skeleton::SetBonesToSetupPose () const {
		int i;
		for (i = 0; i < boneCount_; ++i)
			bones_[i]->SetToSetupPose();
	}
	
	void Skeleton::SetSlotsToSetupPose () const{
		int i;
		for (i = 0; i < slotCount_; ++i)
			slots_[i]->SetToSetupPose();
	}
	
	Bone* Skeleton::FindBone ( std::string boneName) const{
		int i;
		for (i = 0; i < boneCount_; ++i){
			if (data_->GetBoneDataAtIndex(i)->GetName() == boneName){
				return bones_[i];
			}
		}
		return 0;
	}
	
	int Skeleton::FindBoneIndex ( std::string boneName) const{
		int i;
		for (i = 0; i < boneCount_; ++i){
			if (data_->GetBoneDataAtIndex(i)->GetName() == boneName) {
				return i;
			}
		}
		return -1;
	}
	
	Slot* Skeleton::FindSlot ( std::string slotName) const{
		int i;
		for (i = 0; i < slotCount_; ++i){
			if (data_->GetSlotDataAtIndex(i)->GetName() == slotName){
				return slots_[i];
			}
		}
		return 0;
	}
	
	int Skeleton::FindSlotIndex ( std::string slotName) const{
		int i;
		for (i = 0; i < slotCount_; ++i){
			if (data_->GetSlotDataAtIndex(i)->GetName() == slotName){
				return i;
			}
		}
		return -1;
	}
	
	int Skeleton::SetSkinByName ( std::string skinName) {
		Skin *skin;
		if (skinName == "") {
			SetSkin(0);
			return 1;
		}
		skin = data_->FindSkin( skinName);
		if (!skin) return 0;
		SetSkin( skin);
		return 1;
	}
	
	void Skeleton::SetSkin ( Skin* newSkin) {
		if (skin_ && newSkin) newSkin->AttachAll( this, skin_);
		skin_ = newSkin;
	}
	
	Attachment* Skeleton::GetAttachmentForSlotName ( std::string slotName, std::string attachmentName) const{
		int slotIndex = data_->FindSlotIndex( slotName);
		return GetAttachmentForSlotIndex( slotIndex, attachmentName);
	}
	
	Attachment* Skeleton::GetAttachmentForSlotIndex ( int slotIndex, std::string attachmentName) const{
		if (slotIndex == -1) return 0;
		if (skin_) {
			Attachment *attachment = skin_->GetAttachment( slotIndex, attachmentName);
			if (attachment) return attachment;
		}
		if (data_->GetDefaultSkin()) {
			Attachment *attachment = data_->GetDefaultSkin()->GetAttachment(slotIndex, attachmentName);
			if (attachment) return attachment;
		}
		return 0;
	}
	
	int Skeleton::SetAttachment ( std::string slotName, std::string attachmentName) {
		int i;
		for (i = 0; i < slotCount_; ++i) {
			Slot *slot = slots_[i];
			if (slot->GetData()->GetName() == slotName) {
				Attachment* attachment = GetAttachmentForSlotIndex( i, attachmentName);
				if (!attachment) return 0;
				slot->SetAttachment( attachment);
				return 1;
			}
		}
		return 0;
	}
	
	void Skeleton::Update ( float deltaTime) {
		time_ += deltaTime;
	}

	Bone *Skeleton::GetBoneAtIndex(int index){
		return bones_[index];
	}
	
	Bone *Skeleton::GetRoot(){
		return root_;
	}
	
	Slot *Skeleton::GetSlotAtIndex(int index){
		return slots_[index];
	}
	int Skeleton::GetSlotCount(){
		return slotCount_;
	}
	GLKVector4 Skeleton::GetColor(){
		return color_;
	}
	float Skeleton::GetTime(){
		return time_;
	}
	SkeletonData *Skeleton::GetData(){
		return data_;
	}
}
