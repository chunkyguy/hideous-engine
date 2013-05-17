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

#include "Bone.h"
#include <math.h>
#include "GLKMathsAdditions.h"

namespace spine {
	
	void Bone::SetYDown (bool value) {
		yDown_ = value;
	}
	
	Bone::Bone (BoneData* data, Bone* parent)  :
	data_(data),
	parent_(parent),
	xy_(GLKVector2Make(0,0)),
	rotation_(0),
	scale_(GLKVector2Make(0,0)),
	worldXY_(GLKVector2Make(0,0)), // x y
	worldRotation_(0),
	worldScale_(GLKVector2Make(0,0))
	{
		m_.m00 = 0;	m_.m01 = 0;	/* a b  */
		m_.m10 = 0; m_.m11 = 0;	/* c d */

		SetToSetupPose();
	}
	
	void Bone::SetToSetupPose () {
		xy_ = data_->GetXY();
		rotation_ = data_->GetRotation();
		scale_ = data_->GetScale();
	}
	
	void Bone::UpdateWorldTransform ( bool flipX, bool flipY) {
		float radians, cosine, sine;
		if (parent_) {
			
			worldXY_ = GLKVector2Add(parent_->worldXY_, GLKMatrix2Multiply(parent_->m_, xy_));
//			worldXY_.x = xy_.x * parent_->m0001.x + xy_.y * parent_->m0001.y + parent_->worldXY_.x;
//			worldXY_.y = xy_.x * parent_->m1011.x + xy_.y * parent_->m1011.y + parent_->worldXY_.y;

			worldScale_ = GLKVector2Multiply(parent_->worldScale_, scale_);
			worldRotation_ = parent_->worldRotation_ + rotation_;
		} else {
			worldXY_ = xy_;
			worldScale_ = scale_;
			worldRotation_ = rotation_;
		}
		radians = (float)(worldRotation_ * 3.1415926535897932385 / 180);
#ifdef __STDC_VERSION__
		cosine = cosf(radians);
		sine = sinf(radians);
#else
		cosine = (float)cos(radians);
		sine = (float)sin(radians);
#endif
		m_.m00 = cosine * worldScale_.x;
		m_.m10 = sine * worldScale_.x;
		m_.m01 = -sine * worldScale_.y;
		m_.m11 = cosine * worldScale_.y;
		if (flipX) {
			m_.m00 = -m_.m00;
			m_.m01 = -m_.m01;
		}
		if (flipY) {
			m_.m10 = -m_.m10;
			m_.m11 = -m_.m11;
		}
		if (yDown_) {
			m_.m10 = -m_.m10;
			m_.m11 = -m_.m11;
		}
	}
	
	GLKVector2 Bone::GetXY(){
		return xy_;
	}
	void Bone::SetXY(GLKVector2 xy){
		xy_ = xy;
	}
	
	GLKMatrix2 Bone::GetM(){
		return m_;
	}
	GLKVector2 Bone::GetWorldXY(){
		return worldXY_;
	}
	void Bone::SetRotation(float r){
		rotation_ = r;
	}
	float Bone::GetRotation(){
		return rotation_;
	}
	BoneData *Bone::GetData(){
		return data_;
	}
	GLKVector2 Bone::GetScale(){
		return scale_;
	}
	void Bone::SetScale(GLKVector2 s){
		scale_ = s;
	}

}
