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

#ifndef SPINE_REGIONATTACHMENT_H_
#define SPINE_REGIONATTACHMENT_H_

#include "Attachment.h"

#include <GLKit/GLKMath.h>
#include <he/Vertex/VertexData.h>

#include "Slot.h"

namespace he{
	class TextureAtlas;
}

namespace spine {
	
	class RegionAttachment : public Attachment{
	public:
		explicit RegionAttachment (std::string name);
		void SetUVs ( GLKVector4 texCoords, bool rotate);
		void UpdateOffset ();
		he::VertexData ComputeVertices ( Slot* slot);
		he::TextureAtlas* GetRendererObject();
		void SetRendererObject(he::TextureAtlas *atlas);
		void SetRegionOffset(GLKVector2 v);
		void SetRegionSize(GLKVector2 v);
		void SetRegionOriginalSize(GLKVector2 v);
		void SetXY(GLKVector2 xy);
		void SetScale(GLKVector2 scale);
		void SetRotation(float r);
		void SetSize(GLKVector2 size);
		
	private:
		he::VertexData offset_;
		he::TextureAtlas *rendererObject_;
		GLKVector2 regionOffset_;	/* Pixels stripped from the bottom left, unrotated. */
		GLKVector2 regionOriginalSize_;	/* Unrotated, unstripped pixel size. */
		GLKVector2 regionSize_;	/* Unrotated, stripped pixel size. */
		float rotation_;
		GLKVector2 scale_;
		GLKVector2 size_;
		he::VertexData uvs_;
		GLKVector2 xy_;
	};
	
}

#endif /* SPINE_REGIONATTACHMENT_H_ */
