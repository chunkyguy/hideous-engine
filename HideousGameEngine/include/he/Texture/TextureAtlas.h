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
#include <he/Texture/TextureAtlasParser.h>

namespace he{
	class TextureAtlasParser;
	class VertexTex;
	class Texture;
	
	//	Just a wrapper class around the TextureAtlasParser.
	//	Just trying to hide the fact that the parsing is done in ObjC.
	class TextureAtlas{
	public:
		TextureAtlas(std::string data_path);
		~TextureAtlas();
		
		// image_name as stored in the atlas.
		// if width / height are not provided, pick the size from atlas data.
		VertexTex *CreateTextureData(std::string image_name,
									 double width = -1.0, double height = -1.0,
									 bool aspect_correct = true);
		TextureAtlasRegion GetTextureAtlasRegion(std::string image_name);

		void SetTexture(he::Texture * texture);
		he::Texture *GetTexture() const;

	private:
		he::Texture *texture_;
		TextureAtlasParser *parser_;
	};
}
#endif /* defined(__HideousGameEngine__TextureAtlas__) */
