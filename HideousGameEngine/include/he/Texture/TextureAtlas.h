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

#include <he/Utils/GLKMath_Additions.h>

namespace he{
	class TextureAtlasRegion;
	class TextureAtlasParser;
	class TextureVertex;
	class Texture;

	/** Texture Atlas to hold the texture and texture-coordinates
		Just a wrapper class around the TextureAtlasParser.
		Just trying to hide the fact that the parsing is done in ObjC.
	 \warning Owns the texture
	 */
	class TextureAtlas{
	public:
		/** Supported Atlas Formats */
		enum AtlasFormat {
			kZwoptex,	/**< Zwoptex format - Useful when importing from zwoptex.app*/
			kStarling	/**< Starling format - Useful when importing from Flash Pro */
		};

		/** Create a texture Atlas
		 @param data_path Absolute path to the data file.
		 @param texture_path Absolute path to the image file.
		 @param format The format used.
		 */
		TextureAtlas(const std::string &data_path, const std::string &texture_path, const AtlasFormat format);

		/** Dtor */
		~TextureAtlas();
				
		/** Get texture region for image-name/symbol-name inside the sprite sheet
		 @param image_name The symbol-name attached, that can be referred to get the texture region
		 */
		const TextureAtlasRegion *GetTextureAtlasRegion(const std::string &image_name) const;

		/** Get pointer to attached texture 
		 @warning Don't delete the texture. It's owned by the TextureAtlas.
		 */
		he::Texture *GetTexture() const;

	private:
		he::Texture *texture_;		/**< The texture */
		TextureAtlasParser *parser_;	/**< The data parser */
	};
	

	/** Utility function to get vertex-data directly.
		This code avoids refering to TextureAtlasRegion to get the vertex-data.
	 @param atlas The atlas in use.
	 @param image_name As stored in the atlas.
	 @param size If not provided, pick the size from atlas data.
	 @param aspect_correct If true adjusts the image width-wise. Only useful, if width, height changes the original aspect ratio.
	 */
	TextureVertex *CreateTextureData(const TextureAtlas *atlas,
									 const std::string &image_name,
									 const bool aspect_correct = false,
									 const GLKVector2 size = GLKVector2Make(-1, -1));

} /*namespace he*/
#endif /* defined(__HideousGameEngine__TextureAtlas__) */
