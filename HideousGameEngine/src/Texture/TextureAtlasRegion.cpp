//
//  TextureAtlasRegion.cpp
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Texture/TextureAtlasRegion.h>

#include <he/Utils/DebugHelper.h>
namespace he {
	
	TextureAtlasRegion::	TextureAtlasRegion(
											   /*mandatory*/
											   const std::string &name,
											   const GLKVector4 &texture_rect,
											   const GLKVector2 &total_texture_size,
											   /*optional*/
											   const GLKVector2 &sprite_offset,
											   const GLKVector2 &sprite_size,
											   const bool sprite_trimmed,
											   const bool texture_rotated,
											   /*derivable from other data*/
											   const GLKVector4 &sprite_color_rect,
											   const GLKVector2 &sprite_source_size) :
	/*mandatory*/
	name_(name),
	texture_rect_(texture_rect),
	total_texture_size_(total_texture_size),
	/*optional*/
	sprite_offset_(sprite_offset),
	sprite_size_(sprite_size),
	sprite_trimmed_(sprite_trimmed),
	texture_rotated_(texture_rotated),
	/*derivable from other data*/
	sprite_color_rect_(sprite_color_rect),
	sprite_source_size_(sprite_source_size),
	tex_coords_(GLKVector4Make(0, 0, 0, 0))
	{
		calc_tex_coords();
	}

	TextureAtlasRegion::TextureAtlasRegion(
										   /*mandatory*/
										   const std::string &name,
										   const GLKVector4 &texture_rect,
										   const GLKVector2 &total_texture_size,
										   /*optional*/
										   const GLKVector2 &sprite_offset,
										   const GLKVector2 &sprite_size,
										   const bool sprite_trimmed,
										   const bool texture_rotated) :
	/*mandatory*/
	name_(name),
	texture_rect_(texture_rect),
	total_texture_size_(total_texture_size),
	/*optional*/
	sprite_offset_(sprite_offset),
	sprite_size_(sprite_size),
	sprite_trimmed_(sprite_trimmed),
	texture_rotated_(texture_rotated),
	/*derivable from other data*/
	sprite_color_rect_(texture_rect),
	sprite_source_size_(GLKVector2Make(texture_rect.z, texture_rect.w)),
	tex_coords_(GLKVector4Make(0, 0, 0, 0))
	{
		calc_tex_coords();
	}

	void TextureAtlasRegion::calc_tex_coords(){
		float u = texture_rect_.x;
		float v = texture_rect_.y;
		v += texture_rect_.w;
		v = total_texture_size_.y - v;
		float s = u + texture_rect_.z;
		float t = v + texture_rect_.w;
		
		tex_coords_ = GLKVector4Make(u/total_texture_size_.x, v/total_texture_size_.y, s/total_texture_size_.x, t/total_texture_size_.y);
		assert(tex_coords_.x >= 0.0 && tex_coords_.x <= 1.0);
		assert(tex_coords_.y >= 0.0 && tex_coords_.y <= 1.0);
		assert(tex_coords_.z >= 0.0 && tex_coords_.z <= 1.0);
		assert(tex_coords_.w >= 0.0 && tex_coords_.w <= 1.0);

	}
	
	std::ostream &operator<<(std::ostream &os, const TextureAtlasRegion &region)
	{
		os << "region.name: " << region.name_ << "\n"
		<< "region.texture_rect: " << region.texture_rect_ << "\n"
		<< "region.total_texture_size: " << region.total_texture_size_ << "\n"
		<< "region.sprite_offset: " << region.sprite_offset_ << "\n"
		<< "region.sprite_size: " << region.sprite_size_ << "\n"
		<< "region.sprite_trimmed: " << region.sprite_trimmed_ << "\n"
		<< "region.texture_rotated: " << region.texture_rotated_ << "\n"
		<< "region.sprite_color_rect: " << region.sprite_color_rect_ << "\n"
		<< "region.sprite_source_size: " << region.sprite_source_size_ << "\n"
		<< "region.tex_coords: " << region.tex_coords_;
		return os;
	}

}