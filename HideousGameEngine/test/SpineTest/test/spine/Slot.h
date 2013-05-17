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

#ifndef SPINE_SLOT_H_
#define SPINE_SLOT_H_

#include <GLKit/GLKMath.h>

#include "Bone.h"
#include "Attachment.h"
#include "SlotData.h"

namespace spine {
	
	struct Skeleton;
	
	class Slot {
	public:
		Slot(SlotData* data, struct Skeleton* skeleton, Bone* bone);
		~Slot();
		
		/* @param attachment May be 0 to clear the attachment for the slot. */
		void SetAttachment ( Attachment* attachment);
		Attachment *GetAttachment();
		void SetAttachmentTime ( float time);
		float GetAttachmentTime ()const;
		void SetToSetupPose ();
		GLKVector4 GetColor();
		void SetColor(GLKVector4 c);
		Bone *GetBone();
		SlotData *GetData();
		
	private:
		struct Internal{
			float attachmentTime_;
		};
		Internal *internal_;
		SlotData* const data_;
		Skeleton* const skeleton_;
		Bone *bone_;
		GLKVector4 color_;
		Attachment* attachment_;
	};
}

#endif /* SPINE_SLOT_H_ */
