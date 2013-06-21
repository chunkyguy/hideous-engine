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
#include <he/Texture/TextureAtlasRegion.h>
#include <he/Utils/DebugHelper.h>
#include <he/Vertex/TextureVertex.h>

namespace he{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: TextureAtlas
	///////////////////////////////////////////////////////////////////////////////////////////////////
	TextureAtlas::TextureAtlas(const std::string &data_path, const std::string &texture_path, const AtlasFormat format) :
	parser_(nullptr),
	texture_(new he::Texture(texture_path))
	{
		switch(format){
			case kZwoptex:
				parser_ = new ZwoptexDataParser(data_path);
				break;
				
			case kStarling:
				parser_ = new StarlingDataParser(data_path);
				break;
		}
		assert(parser_);		// Uninitialized parser
		assert(texture_);	// Uninitialized texture
	}

	TextureAtlas::~TextureAtlas(){
		delete parser_;
		delete texture_;
	}
	
	bool TextureAtlas::IsTextureRegionAvailable(const std::string &image_name) const{
		const std::map<const std::string, TextureAtlasRegion> map = parser_->GetTable();
		std::map<const std::string, TextureAtlasRegion>::const_iterator itr = map.find(image_name);
		return (itr != map.end());
	}

	const TextureAtlasRegion TextureAtlas::GetTextureAtlasRegion(const std::string &image_name) const{
		const std::map<const std::string, TextureAtlasRegion> map = parser_->GetTable();
		std::map<const std::string, TextureAtlasRegion>::const_iterator itr = map.find(image_name);
		he_Trace("TextureAtlas: fullname '%@' = %@\n",image_name,(itr != map.end())?"Y":"N");
		assert(itr != map.end());
		he_Trace("TextureAtlas: GetTextureAtlasRegion:\n%@\n",itr->second);
		return itr->second;
	}
	
	he::Texture *TextureAtlas::GetTexture() const{
		return texture_;
	}

	TextureVertex *CreateTextureData(const TextureAtlas *atlas,
									 const std::string &image_name,
									 const bool aspect_correct,
									 const GLKVector2 size){
		
		if(atlas->IsTextureRegionAvailable(image_name)){
			const TextureAtlasRegion tex_region = atlas->GetTextureAtlasRegion(image_name);
			return new TextureVertex(tex_region, aspect_correct, size);
		}
		return nullptr;
	}


}//EOF