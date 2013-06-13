//
//  ImageView.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/ImageView.h>

#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/TextureShader.h>
#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Texture/TextureAtlasRegion.h>
#include <he/Vertex/TextureVertex.h>

namespace he {
	namespace ui{
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// MARK: ImageView
		///////////////////////////////////////////////////////////////////////////////////////////////////
		ImageView::ImageView(const ImageViewFactory *factory, const TextureVertex *vertex, const Texture *texture, const Transform transform) :
		View(transform),
		vertex_(nullptr)
		{
			render_object_ = new RenderObject(const_cast<TextureVertex *>(vertex), factory->shader.Get(), const_cast<Texture *>(texture), transform.GetMVP());
		}

		ImageView::ImageView(const ImageViewFactory *factory, const std::string &image_name, const Transform transform) :
		View(transform)
		{
			const TextureAtlasRegion *region = factory->atlas.Get()->GetTextureAtlasRegion(image_name);
			vertex_ = new TextureVertex(region);
			render_object_ = new RenderObject(vertex_, factory->shader.Get(), factory->atlas.Get()->GetTexture(), transform.GetMVP());
		}
		
		ImageView::~ImageView(){
			if(vertex_) {
				delete vertex_;
			}
			delete render_object_;
		}
		
		void ImageView::update(float dt){			
		}
		
		void ImageView::render(){
			render_object_->Render();
		}
		
		void ImageView::refresh(){
			render_object_->SetMVP(GetTransform().GetMVP());
		}
		
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// MARK: ImageViewFactory
		///////////////////////////////////////////////////////////////////////////////////////////////////
		ImageViewFactory::ImageViewFactory(TextureShader *shdr, TextureAtlas *atls){
			shader.Load(shdr, false);
			if(atls){
				atlas.Load(atls, false);
			}
		}

	} /*namespace ui*/
}/*namespace he*/

///EOF

