//
//  TextureAtlas.h
//  HideousGameEngine
//
//  Created by Sid on 12/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__TextureAtlas__
#define __HideousGameEngine__TextureAtlas__

#include <string>

namespace he{
	class Texture;
	class TextureAtlasParser;
	class VertexTex;
	
	//	Just a wrapper class around the TextureAtlasParser.
	//	Just trying to hide the fact that the parsing is done in ObjC.
	class TextureAtlas{
	public:
		TextureAtlas(std::string name, std::string extension);
		VertexTex *createTextureData(std::string name, std::string extension,
									 double width = 100.0, double height = 100.0,
									 bool aspect_correct = true);
		~TextureAtlas();

		Texture *texture_;

	private:
		TextureAtlasParser *parser_;
	};
}
#endif /* defined(__HideousGameEngine__TextureAtlas__) */
