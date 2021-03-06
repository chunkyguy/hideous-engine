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

#include "RegionAttachment.h"
#include <math.h>
#include <he/Texture/TextureAtlas.h>
#include "GLKMathsAdditions.h"

namespace spine {
	
	RegionAttachment::RegionAttachment (std::string name)  :
	Attachment(name, ATTACHMENT_REGION),
	offset_(he::Vertex::V2()),
	rendererObject_(nullptr),
	regionOffset_(GLKVector2Make(0,0)),
	regionOriginalSize_(GLKVector2Make(0,0)),
	regionSize_(GLKVector2Make(0,0)),
	rotation_(0),
	scale_(GLKVector2Make(1,1)),
	size_(GLKVector2Make(0,0)),
	uvs_(he::Vertex::V2()),
	xy_(GLKVector2Make(0,0))
	{	}
	
	void RegionAttachment::SetUVs ( GLKVector4 texCoords, bool rotate) {
		if (rotate) {
			he::Vertex::Set(uvs_, GLKVector2Make(texCoords.z, texCoords.w).v, he::Vertex::kA);
			he::Vertex::Set(uvs_, GLKVector2Make(texCoords.x, texCoords.w).v, he::Vertex::kA);
			he::Vertex::Set(uvs_, GLKVector2Make(texCoords.x, texCoords.y).v, he::Vertex::kA);
			he::Vertex::Set(uvs_, GLKVector2Make(texCoords.z, texCoords.y).v, he::Vertex::kA);
		} else {
			he::Vertex::Set(uvs_, GLKVector2Make(texCoords.x, texCoords.w).v, he::Vertex::kA);
			he::Vertex::Set(uvs_, GLKVector2Make(texCoords.x, texCoords.y).v, he::Vertex::kA);
			he::Vertex::Set(uvs_, GLKVector2Make(texCoords.z, texCoords.y).v, he::Vertex::kA);
			he::Vertex::Set(uvs_, GLKVector2Make(texCoords.z, texCoords.w).v, he::Vertex::kA);
		}
	}
	
	void RegionAttachment::UpdateOffset () {
		GLKVector2 regionScale = GLKVector2Divide(size_, GLKVector2Multiply(regionOriginalSize_, scale_));
		GLKVector2 local = GLKVector2Add(GLKVector2Multiply(GLKVector2DivideScalar(size_, -2), scale_), GLKVector2Multiply(regionOffset_, regionScale));
		GLKVector2 local2 = GLKVector2Add(local, GLKVector2Multiply(regionSize_, regionScale));
		float radians = (float)(rotation_ * 3.1415926535897932385 / 180);
#ifdef __STDC_VERSION__
		float cosine = cosf(radians);
		float sine = sinf(radians);
#else
		float cosine = (float)cos(radians);
		float sine = (float)sin(radians);
#endif
		GLKVector2 localCos = GLKVector2Add(GLKVector2MultiplyScalar(local, cosine), xy_);
		GLKVector2 localSin = GLKVector2MultiplyScalar(local, sine);
		GLKVector2 local2Cos = GLKVector2Add(GLKVector2MultiplyScalar(local2, cosine), xy_);
		GLKVector2 local2Sin = GLKVector2MultiplyScalar(local2, sine);
		he::Vertex::Set(offset_, GLKVector2Make(localCos.x - localSin.y, localCos.y + localSin.x).v, he::Vertex::kA);
		he::Vertex::Set(offset_, GLKVector2Make(localCos.x - local2Sin.y, local2Cos.y + localSin.x).v, he::Vertex::kB);
		he::Vertex::Set(offset_, GLKVector2Make(local2Cos.x - local2Sin.y, local2Cos.y + local2Sin.x).v, he::Vertex::kC);
		he::Vertex::Set(offset_, GLKVector2Make(local2Cos.x - localSin.y, localCos.y + local2Sin.x).v, he::Vertex::kD);
	}
	
	he::Vertex::V2 RegionAttachment::ComputeVertices ( Slot* slot) {
		Bone* bone = slot->GetBone();
		
		GLKVector2 a = GLKVector2Add(bone->GetWorldXY(), GLKMatrix2Multiply(bone->GetM(), he::Vertex::GetVertex(offset_, he::Vertex::kA)));
		GLKVector2 b = GLKVector2Add(bone->GetWorldXY(), GLKMatrix2Multiply(bone->GetM(), he::Vertex::GetVertex(offset_, he::Vertex::kB)));
		GLKVector2 c = GLKVector2Add(bone->GetWorldXY(), GLKMatrix2Multiply(bone->GetM(), he::Vertex::GetVertex(offset_, he::Vertex::kC)));
		GLKVector2 d = GLKVector2Add(bone->GetWorldXY(), GLKMatrix2Multiply(bone->GetM(), he::Vertex::GetVertex(offset_, he::Vertex::kD)));
		he::Vertex::V2 v;
		he::Vertex::Set(v, a, b, c, d);
		return	v;
	}
	
	he::TextureAtlas *RegionAttachment::GetRendererObject(){
		return rendererObject_;
	}
	void RegionAttachment::SetRendererObject(he::TextureAtlas *atlas){
		rendererObject_ = atlas;
	}
	
	void RegionAttachment::SetRegionOffset(GLKVector2 v){
		regionOffset_ = v;
	}
	void RegionAttachment::SetRegionSize(GLKVector2 v){
		regionSize_ = v;
	}
	void RegionAttachment::SetRegionOriginalSize(GLKVector2 v){
		regionOriginalSize_ = v;
	}
	void RegionAttachment::SetXY(GLKVector2 xy){
		xy_ = xy;
	}
	void RegionAttachment::SetScale(GLKVector2 scale){
		scale_ = scale;
	}
	void RegionAttachment::SetRotation(float r){
		rotation_ = r;
	}
	void RegionAttachment::SetSize(GLKVector2 size){
		size_ = size;
	}

}
