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
	
	/** Draw static images */
	class ImageView : public View{
	public:
		/** ImageView from texture */
		ImageView(const Frame frame, const TextureVertex *vertex_m, const TextureShader *shader, const Texture *texture);
		virtual ~ImageView();
		
	protected:
		virtual void update(float dt);
		virtual void render();
		
		const TextureVertex *vertex_;
		RenderObject *render_object_;
	};
}

#endif
