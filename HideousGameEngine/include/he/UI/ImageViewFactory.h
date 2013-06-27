//
//  ImageViewFactory.h
//  HideousGameEngine
//
//  Created by Sid on 27/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_ImageViewFactory_h
#define HideousGameEngine_ImageViewFactory_h
#include <string>

#include <he/Texture/TextureAtlas.h>
#include <he/Utils/Asset.h>
#include <he/Utils/Transform.h>

namespace he {
	class ImageView;
	class Sprite;
	class Texture;
	class TextureAtlas;
	class TextureShader;
	
	/** Factory to create ImageView
	 Can be configured to create ImageView from atlas or from directly from attached texture
	 */
	class ImageViewFactory{
	public:
		/** Create ImageViewFactory
		 @param shader The texture shader. Does not owns
		 @param atlas_m The atlas. Owns it.
		 @param texture_m The texture. Owns it.
		 */
		ImageViewFactory(TextureShader *shader, TextureAtlas *atlas_m = nullptr, Texture *texture_m = nullptr);
		
		/** Create with atlas 
		 @param shader The texture shader. Does not owns
		 @param data_path The data path of texture-atlas
		 @param img_path The image path of the texture-atlas
		 @param format The texture-atlas format
		 */
		ImageViewFactory(TextureShader *shader, const std::string &data_path, const std::string &img_path, TextureAtlas::AtlasFormat format);
		
		/** Create with texture 
		 @param shader The texture shader. Does not owns
		 @param img_path The image path of the texture
		 */
		ImageViewFactory(TextureShader *shader, const std::string &img_path);
		
		/** Creates ImageView from attached texture
		 @param trans The transform of the view
		 @returns ImageView instance
		 */
		ImageView *CreateImageView(Transform trans);
		
		/** Create ImageView from attached texture atlas
		 @param trans The transform of the view
		 @param region_name The name stored in the atlas.
		 @returns ImageView instance
		 */
		ImageView *CreateImageView(Transform trans, const std::string region_name);

		/** Create Sprite from attached texture atlas
		 @param trans The transform of the view
		 @param region_name The name stored in the atlas.
		 @param repeat_count Number of times the animation should repeat. Default is infinite.
		 @param final_frame The frame to be used when the animation stops. Default is 0
		 @param fps The speed of the animation. Default is 24
		 @returns Sprite instance
		 */
		Sprite *CreateSprite(Transform trans, const std::string region_name,
							 const int repeat_count = -1, const int final_frame = 0, const float fps = 24.0f);

	private:
		Asset<TextureAtlas> atlas;
		Asset<TextureShader> shader;
		Asset<Texture> texture;
	};
}

#endif
