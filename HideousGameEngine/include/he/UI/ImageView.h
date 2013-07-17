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

namespace he {
	
	class RenderObject;
	class Texture;
	class TextureVertex;
	class TextureShader;
	class TextureAtlas;
	
	/** Draw static images */
	class Image {
	public:
		Image(const TextureVertex *vertex_m, const TextureShader *shader, const Texture *texture);
		~Image();
		void Render(const Frame &frame);

	private:
		const TextureVertex *vertex_;
		RenderObject *render_object_;
	};
	
	namespace image {
		Image *Create(const TextureShader *shader, const Texture *texture);
		Image *Create(const TextureShader *shader, const TextureAtlas *texture_atlas, const std::string &region);
	}
	
	class ImageView : public View{
	public:
		/** ImageView from texture */
		ImageView(const Frame frame, Image *image);
		virtual ~ImageView();
		virtual void Update(float dt);
		virtual void Render();
		
	private:
		Image *image_;
	};
}

#endif
