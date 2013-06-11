//
//  TextureVertex.cpp
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Vertex/TextureVertex.h>

#include <he/Texture/TextureAtlasRegion.h>

namespace he{
	
	TextureVertex::TextureVertex(const Vertex::V2 &position_data, const Vertex::V2 &texture_data) :
	IVertex(4),
	position_data_(position_data),
	texture_data_(texture_data)
	{}

	
	TextureVertex::TextureVertex(float width, float height, bool aspect_lock, GLKVector4 texture_coords) :
	IVertex(4),
	position_data_(),
	texture_data_()
	{
		GLKVector4 pos_coords = GLKVector4Make(-width/2.0f, -height/2.0f, width/2.0f, height/2.0f);
		set_data(pos_coords, texture_coords, aspect_lock);
	}

	TextureVertex::TextureVertex(const TextureAtlasRegion *region, float width, float height, const bool aspect_lock) :
	IVertex(4),
	position_data_(),
	texture_data_()
	{
		if(width < 0.0){
			width = region->sprite_size_.x;
		}
		if(height < 0.0){
			height = region->sprite_size_.y;
		}

		GLKVector4 pos_coords = GLKVector4Make(-width/2.0f, -height/2.0f, width/2.0f, height/2.0f);
		set_data(pos_coords, region->tex_coords_, aspect_lock);
	}

	void TextureVertex::set_data(const GLKVector4 &pos_coords, const GLKVector4 &tex_coords, const bool aspect_lock){
		GLKVector2 pos_min = GLKVector2Make(pos_coords.x, pos_coords.y);
		GLKVector2 pos_max = GLKVector2Make(pos_coords.z, pos_coords.w);
		Vertex::Set(position_data_, pos_min, pos_max);
		GLKVector2 tex_min = GLKVector2Make(tex_coords.x, tex_coords.y);
		GLKVector2 tex_max = GLKVector2Make(tex_coords.z, tex_coords.w);
		Vertex::Set(texture_data_, tex_min, tex_max);
		if(aspect_lock){
			apply_aspect_correctnes(tex_coords);
		}
	}

	void TextureVertex::apply_aspect_correctnes(const GLKVector4 &texture_coords){
		float eff_w = texture_coords.z - texture_coords.x;
		float eff_h = texture_coords.w - texture_coords.y;
		float aspect_ratio;
		if(eff_w < eff_h){
			aspect_ratio = eff_w/eff_h;
			GLKVector2 scale = GLKVector2Make(aspect_ratio, 1.0f);
			he::Vertex::Scale(position_data_, scale);
		}else if(eff_h < eff_w){
			aspect_ratio = eff_h/eff_w;
			GLKVector2 scale = GLKVector2Make(1.0f, aspect_ratio);
			he::Vertex::Scale(position_data_, scale);
		}
	}

	const GLfloat *TextureVertex::GetRawData(const DataType dt) const{
		switch(dt){
			case IVertex::kPosition:
				return &position_data_.data[0]; break;
				
			case IVertex::kColor:
				return nullptr;

			case IVertex::kTexture:
				return &texture_data_.data[0]; break;
		}
		return nullptr;
	}

	const Vertex::V2 &TextureVertex::GetVertexPositionData() const{
		return position_data_;
	}
	const Vertex::V2 &TextureVertex::GetVertexTextureData() const{
		return texture_data_;
	}

}