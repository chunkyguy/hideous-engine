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
#include <he/Texture/Texture.h>
#include <he/Utils/Asset.h>
#include <he/Utils/Transform.h>

namespace he {
	class Sprite;
	class SpriteView;
	class Image;
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
		
		ImageViewFactory(TextureShader *shader);
		
		/** Create with atlas 
		 @param shader The texture shader. Does not owns
		 @param data_path The data path of texture-atlas
		 @param img_path The image path of the texture-atlas
		 @param format The texture-atlas format
		 */
		void SetAtlas(const std::string &data_path, const std::string &img_path, TextureAtlas::AtlasFormat format);
		
		/** Create with texture 
		 @param shader The texture shader. Does not owns
		 @param img_path The image path of the texture
		 */
		void SetImage(const std::string &img_path);
		
		/** Creates ImageView from attached texture
		 @param trans The transform of the view
		 @returns ImageView instance
		 */
		ImageView *CreateImageView(Transform &transform);
		
		/** Create ImageView from attached texture atlas
		 @param trans The transform of the view
		 @param region_name The name stored in the atlas.
		 @returns ImageView instance
		 */
		ImageView *CreateImageView(Transform &transform, const std::string &region_name);

		/** Create Sprite from attached texture atlas
		 @param trans The transform of the view
		 @param region_name The name stored in the atlas.
		 @param repeat_count Number of times the animation should repeat. Default is infinite.
		 @param final_frame The frame to be used when the animation stops. Default is 0
		 @param fps The speed of the animation. Default is 24
		 @returns Sprite instance
		 */
		void LoadSprite(const std::string region_name,
							 const int repeat_count = -1, const int final_frame = 0, const float fps = 24.0f);

		SpriteView *CreateSpriteView(Transform &transform);

	private:
		Asset<TextureAtlas> atlas_m_;
		Asset<Texture> texture_m_;
		Asset<TextureShader> shader_;
		Asset<Image> image_m_;
		Asset<Sprite> sprite_m_;
		Asset<TextureVertex> tex_vertex_m_;
	};
}

#endif
