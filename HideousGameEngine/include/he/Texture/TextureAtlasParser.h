//
//  TextureAtlasParser.h
//  HideousGameEngine
//
//  Created by Sid on 12/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
#ifndef __HideousGameEngine__TextureAtlasParser__
#define __HideousGameEngine__TextureAtlasParser__

#include <he/Utils/GLKMath_Additions.h>
#include <string>
#include <map>

namespace he{
	
	struct TextureAtlasRegion{
		std::string name;
		GLKVector4 sprite_color_rect;
		GLKVector2 sprite_offset;
		GLKVector2 sprite_size;
		GLKVector2 sprite_source_size;
		bool sprite_trimmed;
		GLKVector4 texture_rect;
		bool texture_rotated;
		GLKVector4 tex_coords;
	};
	
	//	Parse the texture altas that is in the plist format created by zwoptex.app
	//	Store normalized {name, tex_coord} in map.
	class TextureAtlasParser{
	public:
		TextureAtlasParser(std::string &path);
		~TextureAtlasParser();
		std::map<std::string, TextureAtlasRegion> &GetTable();
		
	private:
		GLKVector2 size_;
		std::map<std::string, TextureAtlasRegion> table_;
	};
	
	
}
#endif
