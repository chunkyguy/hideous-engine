//
//  VertexTex.cpp
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Vertex/VertexTex.h>

#include <he/Texture/TextureAtlasRegion.h>

namespace he{
	
	VertexTex::VertexTex(const VertexData &position_data, const VertexData &texture_data) :
	IVertex(4),
	position_data_(position_data),
	texture_data_(texture_data)
	{}

	
	VertexTex::VertexTex(float width, float height, bool aspect_lock, GLKVector4 texture_coords) :
	IVertex(4),
	position_data_(VertexData(-width/2.0, -height/2.0, width/2.0, height/2.0)),
	texture_data_(texture_coords)
	{
		if(aspect_lock){
			apply_aspect_correctnes(texture_coords);
		}
	}

	VertexTex::VertexTex(const TextureAtlasRegion *region, float width, float height, const bool aspect_lock) :
	IVertex(4),
	position_data_(),
	texture_data_(region->tex_coords_)
	{
		if(width < 0.0){
			width = region->sprite_size_.x;
		}
		if(height < 0.0){
			height = region->sprite_size_.y;
		}
		
		position_data_ = VertexData(-width/2.0, -height/2.0, width/2.0, height/2.0);
		if(aspect_lock){
			apply_aspect_correctnes(region->tex_coords_);
		}
	}

	void VertexTex::apply_aspect_correctnes(const GLKVector4 &texture_coords){
		float eff_w = texture_coords.z - texture_coords.x;
		float eff_h = texture_coords.w - texture_coords.y;
		float aspect_ratio;
		if(eff_w < eff_h){
			aspect_ratio = eff_w/eff_h;
			position_data_.Scale(aspect_ratio, 1.0);
		}else if(eff_h < eff_w){
			aspect_ratio = eff_h/eff_w;
			position_data_.Scale(1.0, aspect_ratio);
		}
	}
	
	const GLfloat *VertexTex::GetPositionData() const{
		return position_data_.GetData();
	}
	const GLfloat *VertexTex::GetTextureData() const{
		return texture_data_.GetData();
	}
	const VertexData &VertexTex::GetVertexPositionData() const{
		return position_data_;
	}
	const VertexData &VertexTex::GetVertexTextureData() const{
		return texture_data_;
	}

}