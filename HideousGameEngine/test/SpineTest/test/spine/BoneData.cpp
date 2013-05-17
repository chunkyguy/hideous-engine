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

#include "BoneData.h"
 

namespace spine {
	
	BoneData::BoneData (std::string name, BoneData* parent, float length, float rotation, GLKVector2 scale, GLKVector2 xy) :
	name_(name),
	parent_(parent),
	length_(length),
	rotation_(rotation),
	scale_(scale),
	xy_(xy)
	{	}
	
	GLKVector2 BoneData::GetXY(){
		return xy_;
	}
	void BoneData::SetXY(GLKVector2 xy){
		xy_ = xy;
	}
	GLKVector2 BoneData::GetScale(){
		return scale_;
	}
	void BoneData::SetScale(GLKVector2 scale){
		scale_ = scale;
	}
	float BoneData::GetRotation(){
		return rotation_;
	}
	void BoneData::SetRotation(float r){
		rotation_ = r;
	}
	BoneData *BoneData::GetParent(){
		return parent_;
	}
	std::string BoneData::GetName(){
		return name_;
	}
	void BoneData::SetLength(float len){
		length_ = len;
	}
}
