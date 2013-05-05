//
//  TextureAtlas.cpp
//  HideousGameEngine
//
//  Created by Sid on 12/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Texture/TextureAtlas.h>

#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlasParser.h>
#include <he/Utils/DebugLog.h>
#include <he/Vertex/VertexTex.h>

namespace he{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: TextureAtlas
	///////////////////////////////////////////////////////////////////////////////////////////////////
	TextureAtlas::TextureAtlas(std::string name, std::string extension)
	{
		texture_ = new Texture(name, extension);
		parser_ = new TextureAtlasParser(name);
	}

	TextureAtlas::~TextureAtlas(){
		delete texture_;
		delete parser_;
	}

	VertexTex *TextureAtlas::createTextureData(std::string name, std::string extension,
											   double width, double height, bool aspect_correct ){
		std::map<std::string, GLKVector4>::iterator itr = parser_->GetTable().find(name+"."+extension);
		assert(itr != parser_->GetTable().end());
		FILE_LOG(logDEBUG) << "TextureAtlas: get texture: " << name << "." << extension;
		return new VertexTex(width, height, aspect_correct, itr->second);
	}

}//EOF