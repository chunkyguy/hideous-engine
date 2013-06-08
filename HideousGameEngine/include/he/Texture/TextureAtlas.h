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
	class TextureAtlasRegion;
	class TextureAtlasParser;
	class VertexTex;
	class Texture;
	
	//	Just a wrapper class around the TextureAtlasParser.
	//	Just trying to hide the fact that the parsing is done in ObjC.
	class TextureAtlas{
	public:
		enum AtlasFormat {Zwoptex, Starling};

		//	Owns the texture
		TextureAtlas(const std::string &data_path, const std::string &texture_path, const AtlasFormat format);
		~TextureAtlas();
				
		const TextureAtlasRegion *GetTextureAtlasRegion(const std::string &image_name) const;

		he::Texture *GetTexture() const;

	private:
		he::Texture *texture_;
		TextureAtlasParser *parser_;
	};
	
	// image_name as stored in the atlas.
	// if width / height are not provided, pick the size from atlas data.
	VertexTex *CreateTextureData(const TextureAtlas *atlas,
								 const std::string &image_name,
								 float width = -1.0,
								 float height = -1.0,
								 const bool aspect_correct = true);

} /*namespace he*/
#endif /* defined(__HideousGameEngine__TextureAtlas__) */
