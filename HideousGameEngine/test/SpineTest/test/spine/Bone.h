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

#ifndef SPINE_BONE_H_
#define SPINE_BONE_H_
#include <GLKit/GLKMath.h>

#include "BoneData.h"

namespace spine {
	
	class Bone {
	public:
		/* @param parent May be 0. */
		Bone (BoneData* data, Bone* parent);
		~Bone (){};

		void SetYDown (bool yDown);

		void SetToSetupPose ();
		void UpdateWorldTransform ( bool flipX, bool flipY);
		GLKVector2 GetXY();
		void SetXY(GLKVector2 xy);
		GLKMatrix2 GetM();
		GLKVector2 GetWorldXY();
		float GetRotation();
		void SetRotation(float r);
		BoneData *GetData();
		GLKVector2 GetScale();
		void SetScale(GLKVector2 s);
		
	private:
		BoneData *data_;
		Bone *parent_;
		GLKVector2 xy_;	// x_, y_
		float rotation_;
		GLKVector2 scale_;	//scaleX_, scaleY_;
		
//		float m00_, m01_, worldX_; /* a b x */
//		float m10_, m11_, worldY_; /* c d y */
		GLKVector2 worldXY_;		//worldX_, worldY_
		GLKMatrix2 m_;// m00_, m01_, m10_, m11_
		float worldRotation_;
		GLKVector2 worldScale_;	//worldScaleX_, worldScaleY_;
		bool yDown_;
	};
	
}

#endif /* SPINE_BONE_H_ */
