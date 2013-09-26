//
//  TextureAtlasParser.h
//  HideousGameEngine
//
//  Created by Sid on 12/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
#ifndef __HideousGameEngine__TextureAtlasParser__
#define __HideousGameEngine__TextureAtlasParser__

#include <string>
#include <map>

#include <he/Utils/GLKMath_Additions.h>
#include <he/Texture/TextureAtlasRegion.h>

namespace he{
	
	//	Store normalized {name, tex_coord} in map.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: TextureAtlasParser
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class TextureAtlasParser{
	public:
		virtual ~TextureAtlasParser(){};
		virtual	const std::map<const std::string, TextureAtlasRegion> &GetTable() const = 0;
	};
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ZwoptexDataParser
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	Parse the texture altas that is in the plist format created by zwoptex.app
	class ZwoptexDataParser : public TextureAtlasParser{
	public:
		ZwoptexDataParser(const std::string &path);
		~ZwoptexDataParser();
		const std::map<const std::string, TextureAtlasRegion> &GetTable() const;
		
	private:
		GLKVector2 size_;
		std::map<const std::string, TextureAtlasRegion> table_;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: StarlingDataParser
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	Parse the texture altas that is in the xml format created by Flash Professional.
	class StarlingDataParser : public TextureAtlasParser{
	public:
		StarlingDataParser(const std::string &path, const GLKVector2 image_size);
		~StarlingDataParser();
		const std::map<const std::string, TextureAtlasRegion> &GetTable() const;
		
	private:
		GLKVector2 size_;
		std::map<const std::string, TextureAtlasRegion> table_;
	};
	
}
#endif
