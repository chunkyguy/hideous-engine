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

#include "AtlasAttachmentLoader.h"
#include <he/Texture/TextureAtlas.h>
#include <he/Texture/TextureAtlasRegion.h>
#include "RegionAttachment.h"

namespace spine {

	AtlasAttachmentLoader::AtlasAttachmentLoader (he::TextureAtlas* atlas)  :
	atlas_(atlas)
	{	}

	Attachment* AtlasAttachmentLoader::NewAttachment ( Skin* skin, AttachmentType type, std::string name){
		
		switch (type) {
			case ATTACHMENT_REGION: {
				std::string eff_name = name + ".png";	// becuase the json file doesn't has .png appended
				printf("AtlasAttachmentLoader: NewAttachment: %s\n",eff_name.c_str());
				const he::TextureAtlasRegion region = atlas_->GetTextureAtlasRegion(eff_name);
				
				RegionAttachment* attachment = new RegionAttachment(eff_name);
				attachment->SetRendererObject(atlas_);
				attachment->SetUVs(region.tex_coords_, region.texture_rotated_);
				attachment->SetRegionOffset(region.sprite_offset_);
				attachment->SetRegionSize( region.sprite_size_);
				attachment->SetRegionOriginalSize(region.sprite_source_size_);
				return attachment;
			}
			default:
				AttachmentLoader::SetUnknownTypeError( type);
				return 0;
		}
	}
}
