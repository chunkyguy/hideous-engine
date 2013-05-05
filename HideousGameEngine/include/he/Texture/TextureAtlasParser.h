//
//  TextureAtlasParser.h
//  HideousGameEngine
//
//  Created by Sid on 12/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
#ifndef __HideousGameEngine__TextureAtlasParser__
#define __HideousGameEngine__TextureAtlasParser__

#include <GLKit/GLKMath.h>
#include <string>
#include <map>

namespace he{
	
	//	Parse the texture altas that is in the plist format created by zwoptex.app
	//	Store normalized {name, tex_coord} in map.
	class TextureAtlasParser{
	public:
		TextureAtlasParser(std::string &name);
		~TextureAtlasParser();
		std::map<std::string, GLKVector4> &GetTable();
		
	private:
		std::map<std::string, GLKVector4> table_;
	};
	
	
}
#endif
