//
//  TextureAtlas.cpp
//  HideousGameEngine
//
//  Created by Sid on 12/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Texture/TextureAtlas.h>

#include <he/Texture/Texture.h>
#include <he/Utils/DebugLog.h>
#include <he/Vertex/VertexTex.h>

namespace he{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: TextureAtlas
	///////////////////////////////////////////////////////////////////////////////////////////////////
	TextureAtlas::TextureAtlas(std::string image_path, std::string data_path)
	{
		texture_ = new Texture(image_path);
		parser_ = new TextureAtlasParser(data_path);
	}

	TextureAtlas::~TextureAtlas(){
		delete texture_;
		delete parser_;
	}

	VertexTex *TextureAtlas::createTextureData(std::string image_name,
											   double width, double height, bool aspect_correct ){
		TextureAtlasRegion tex_region = GetTextureAtlasRegion(image_name);
		FILE_LOG(logDEBUG) << "TextureAtlas: get texture: " << image_name;
		if(width < 0.0){
			width = tex_region.sprite_size.x;
		}
		if(height < 0.0){
			height = tex_region.sprite_size.y;
		}
		return new VertexTex(width, height, aspect_correct, tex_region.tex_coords);
	}
	
	TextureAtlasRegion TextureAtlas::GetTextureAtlasRegion(std::string image_name){
		std::map<std::string, TextureAtlasRegion>::iterator itr = parser_->GetTable().find(image_name);
		assert(itr != parser_->GetTable().end());
		return itr->second;
	}

}//EOF