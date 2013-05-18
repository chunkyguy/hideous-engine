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

#include "Slot.h"
 
#include "Skeleton.h"

namespace spine {
	
	
	Slot::Slot (SlotData* data, Skeleton* skeleton, Bone* bone) :
	attachment_(nullptr),
	attachmentTime_(0.0),
	bone_ (bone),
	color_(GLKVector4Make(1,1,1,1)),
	data_ (data),
	skeleton_( skeleton)
	{
		SetToSetupPose();
	}
	
	
	void Slot::SetAttachment ( Attachment* attachment) {
		attachment_ = attachment;
		attachmentTime_ = skeleton_->GetTime();
	}
	
	Attachment *Slot::GetAttachment(){
		return attachment_;
	}
	
	void Slot::SetAttachmentTime ( float time) {
		attachmentTime_ = skeleton_->GetTime() - time;
	}
	
	float Slot::GetAttachmentTime () const {
		return skeleton_->GetTime() - attachmentTime_;
	}
	
	void Slot::SetToSetupPose () {
		
		Attachment* attachment = 0;
		color_ = data_->GetColor();
		
		if (!data_->GetAttachmentName().empty()) {
			/* Find slot index. */
			int i;
			for (i = 0; i < skeleton_->GetData()->GetSlotCount(); ++i) {
				if (data_ == skeleton_->GetData()->GetSlotDataAtIndex(i)) {
					attachment = skeleton_->GetAttachmentForSlotIndex( i, data_->GetAttachmentName());
					break;
				}
			}
		}
		SetAttachment( attachment);
	}
	
	GLKVector4 Slot::GetColor(){
		return color_;
	}
	void Slot::SetColor(GLKVector4 c){
		color_ = c;
	}
	Bone *Slot::GetBone(){
		return bone_;
	}
	SlotData *Slot::GetData(){
		return data_;
	}
}
