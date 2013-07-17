//
//  ImageViewFactory.cpp
//  HideousGameEngine
//
//  Created by Sid on 27/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/ImageViewFactory.h>

#include <he/Shaders/TextureShader.h>
#include <he/Texture/TextureAtlasRegion.h>
#include <he/Vertex/TextureVertex.h>
#include <he/Utils/Frame.h>
#include <he/UI/ImageView.h>
#include <he/UI/Sprite.h>
#include <he/Utils/Utils.h>

namespace he{
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ImageViewFactory
	///////////////////////////////////////////////////////////////////////////////////////////////////
	ImageViewFactory::ImageViewFactory(TextureShader *shader) {
		shader_.Set(shader);
	}
	
	void ImageViewFactory::SetAtlas(const std::string &data_path, const std::string &img_path, TextureAtlas::AtlasFormat format){
		atlas_m_.Move( new TextureAtlas(data_path, img_path, format));
	}
	
	void ImageViewFactory::SetImage(const std::string &img_path){
		assert(!shader_.IsEmpty());
		
		texture_m_.Move(new Texture(img_path));
		tex_vertex_m_.Move(new TextureVertex(texture_m_.Get()->GetSize()), true);
		image_m_.Move(new Image(tex_vertex_m_.Get(), shader_.Get(), texture_m_.Get()), true);
	}
	
	ImageView *ImageViewFactory::CreateImageView(Transform &transform){
		assert(!texture_m_.IsEmpty());
		assert(!image_m_.IsEmpty());
		return new ImageView(transform, image_m_.Get());
	}
	
	ImageView *ImageViewFactory::CreateImageView(Transform &transform, const std::string &region_name){
		assert(!atlas_m_.IsEmpty());
		assert(!shader_.IsEmpty());
		
		const TextureAtlasRegion region = atlas_m_.Get()->GetTextureAtlasRegion(region_name);
		tex_vertex_m_.Move(new TextureVertex(region), true);
		image_m_.Move(new Image(tex_vertex_m_.Get(), shader_.Get(), atlas_m_.Get()->GetTexture()), true);
		return new ImageView(transform,	image_m_.Get());
	}

	void ImageViewFactory::LoadSprite(const std::string region_name,
										   const int repeat_count, const int final_frame, const float fps){
		assert(!atlas_m_.IsEmpty());
		assert(!shader_.IsEmpty());
		
		const TextureAtlasRegion region = atlas_m_.Get()->GetTextureAtlasRegion(FlashFullName(region_name));
		sprite_m_.Move(new Sprite(region_name, shader_.Get(), atlas_m_.Get(), repeat_count, final_frame, fps), true);
	}

	SpriteView *ImageViewFactory::CreateSpriteView(Transform &transform) {
		assert(!sprite_m_.IsEmpty());
		return new SpriteView(transform, sprite_m_.Get());
	}
	
}