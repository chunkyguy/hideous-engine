//
//  ImageView.h
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_ImageView_h
#define HideousGameEngine_ImageView_h
#include <string>

#include <he/UI/View.h>

#include <he/Utils/Frame.h>
#include <he/Utils/Asset.h>

namespace he {
	
	class RenderObject;
	class Texture;
	class TextureAtlas;
	class TextureShader;
	class TextureVertex;
	
		
		/** Factory to create ImageView*/
		struct ImageViewFactory{
			ImageViewFactory(TextureShader *shdr, TextureAtlas *atls = nullptr);
			
			Asset<TextureAtlas> atlas;
			Asset<TextureShader> shader;
		};
		
		/** Draw static images */
		class ImageView : public View{
		public:
			/** ImageView from texture */
			ImageView(const Frame frame, const ImageViewFactory *factory, const he::TextureVertex *vertex, const he::Texture *texture);

			/** ImageView from atlas */
			ImageView(const Frame frame, const ImageViewFactory *factory, const std::string &image_name);
			
			virtual ~ImageView();
			
		protected:
			virtual void update(float dt);
			virtual void render();

			RenderObject *render_object_;
			TextureVertex *vertex_;
		};
}

#endif
