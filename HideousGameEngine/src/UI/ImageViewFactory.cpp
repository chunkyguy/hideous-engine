//
//  ImageViewFactory.cpp
//  HideousGameEngine
//
//  Created by Sid on 27/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/ImageViewFactory.h>

#include <he/Shaders/TextureShader.h>
#include <he/Texture/Texture.h>
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
	ImageViewFactory::ImageViewFactory(TextureShader *shdr, TextureAtlas *atlas_m, Texture *texture_m){
		shader.Set(shdr);
		if(atlas_m){
			atlas.Set(atlas_m);
		}
		if(texture_m){
			texture.Set(texture_m);
		}
	}
	
	ImageViewFactory::ImageViewFactory(TextureShader *shdr, const std::string &data_path, const std::string &img_path, TextureAtlas::AtlasFormat format){
		shader.Set(shdr);
		atlas.Move( new TextureAtlas(data_path, img_path, format));
	}
	
	ImageViewFactory::ImageViewFactory(TextureShader *shdr, const std::string &img_path){
		shader.Set(shdr);
		texture.Move(new Texture(img_path));
	}
	
	ImageView *ImageViewFactory::CreateImageView(Transform trans){
		return new ImageView(Frame(trans, texture.Get()->GetSize()),				//	Frame
							 new TextureVertex(texture.Get()->GetSize()),		//	Vertex-data
							 shader.Get(),										//	Shader
							 texture.Get());										//	Texture
	}
	
	ImageView *ImageViewFactory::CreateImageView(Transform trans, const std::string region_name){
		const TextureAtlasRegion region = atlas.Get()->GetTextureAtlasRegion(region_name);
		return new ImageView(Frame(trans, region.sprite_size_),					//	Frame
							 new TextureVertex(region),							//	Vertex-data
							 shader.Get(),										//	Shader
							 atlas.Get()->GetTexture());							//	Texture
	}

	Sprite *ImageViewFactory::CreateSprite(Transform trans, const std::string region_name,
										   const int repeat_count, const int final_frame, const float fps){
		const TextureAtlasRegion region = atlas.Get()->GetTextureAtlasRegion(FlashFullName(region_name));
		return new Sprite(Frame(trans, region.sprite_size_),					//	Frame
						  region_name,										//	Vertex-data
						  shader.Get(),										//	Shader
						  atlas.Get(),										//	TextureAtlas
						  repeat_count,
						  final_frame,
						  fps);
	}

	
}