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

#ifndef SPINE_BONEDATA_H_
#define SPINE_BONEDATA_H_

#include <string>
#include <he/Utils/GLKMath_Additions.h>

namespace spine {
	
	class BoneData {
	public:
		BoneData (std::string name = "", BoneData* parent = 0,
				  float length = 0, float rotation = 0,
				  GLKVector2 scale = GLKVector2Make(1,1), GLKVector2 xy = GLKVector2Make(0,0));
		
		GLKVector2 GetXY();
		void SetXY(GLKVector2 xy);
		GLKVector2 GetScale();
		void SetScale(GLKVector2 scale);
		float GetRotation();
		void SetRotation(float r);
		BoneData *GetParent();
		std::string GetName();
		void SetLength(float len);
		
	private:
		float length_;
		std::string name_;
		BoneData *parent_;
		float rotation_;
		GLKVector2 scale_;	// scaleX_, scaleY_;
		GLKVector2 xy_;	// x_, y_;
	};
	
	
}

#endif /* SPINE_BONEDATA_H_ */
