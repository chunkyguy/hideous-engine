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

#ifndef SPINE_SKELETON_H_
#define SPINE_SKELETON_H_
#include <GLKit/GLKMath.h>

#include "SkeletonData.h"
#include "Slot.h"
#include "Skin.h"

namespace spine {
	class Skeleton {
	public:
		explicit Skeleton (SkeletonData* data);
		~Skeleton ();
		
		void UpdateWorldTransform () const;
		
		void SetToSetupPose () const;
		void SetBonesToSetupPose () const;
		void SetSlotsToSetupPose () const;
		
		/* Returns 0 if the bone was not found. */
		Bone* FindBone ( std::string boneName) const;
		/* Returns -1 if the bone was not found. */
		int FindBoneIndex ( std::string boneName) const;
		
		/* Returns 0 if the slot was not found. */
		Slot* FindSlot ( std::string slotName) const;
		/* Returns -1 if the slot was not found. */
		int FindSlotIndex ( std::string slotName) const;
		
		/* Sets the skin used to look up attachments not found in the SkeletonData defaultSkin. Attachments from the new skin are
		 * attached if the corresponding attachment from the old skin was attached.
		 * @param skin May be 0.*/
		void SetSkin ( Skin* skin);
		/* Returns 0 if the skin was not found. See Skeleton_setSkin.
		 * @param skinName May be 0. */
		int SetSkinByName ( std::string skinName);
		
		/* Returns 0 if the slot or attachment was not found. */
		Attachment* GetAttachmentForSlotName ( std::string slotName, std::string attachmentName) const;
		/* Returns 0 if the slot or attachment was not found. */
		Attachment* GetAttachmentForSlotIndex ( int slotIndex, std::string attachmentName) const;
		/* Returns 0 if the slot or attachment was not found. */
		int SetAttachment ( std::string slotName, std::string attachmentName);
		
		void Update ( float deltaTime);
		Bone *GetBoneAtIndex(int index);
		Bone *GetRoot();
		Slot *GetSlotAtIndex(int index);
		int GetSlotCount();
		GLKVector4 GetColor();
		float GetTime();
		SkeletonData *GetData();
		
	private:
		Bone** bones_;
		int boneCount_;
		GLKVector4 color_;
		SkeletonData *data_;
		Slot** drawOrder_;
		bool flipX_, flipY_;
		Bone* root_;
		Skin* skin_;
		int slotCount_;
		Slot** slots_;
		float time_;
	};
}

#endif /* SPINE_SKELETON_H_*/
