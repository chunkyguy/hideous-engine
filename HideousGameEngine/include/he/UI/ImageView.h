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

#include <he/Utils/Transform.h>
#include <he/Utils/Asset.h>

namespace he {
	
	class RenderObject;
	class Texture;
	class TextureAtlas;
	class TextureShader;
	class TextureVertex;
	
	namespace ui{
		
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
			ImageView(const ImageViewFactory *factory, const he::TextureVertex *vertex, const he::Texture *texture, const Transform transform = Transform());

			/** ImageView from atlas */
			ImageView(const ImageViewFactory *factory, const std::string &image_name, const Transform transform = Transform());
			
			~ImageView();
			
		private:
			void update(float dt);
			void render();
			void refresh();
			
			RenderObject *render_object_;
			TextureVertex *vertex_;
		};
	}
}

#endif
