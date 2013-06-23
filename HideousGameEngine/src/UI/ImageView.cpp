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
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// MARK: ImageView
		///////////////////////////////////////////////////////////////////////////////////////////////////
		ImageView::ImageView(const Frame frame, const ImageViewFactory *factory, const TextureVertex *vertex, const Texture *texture) :
		View(frame),
		vertex_(nullptr)
		{
			render_object_ = new RenderObject(const_cast<TextureVertex *>(vertex), factory->shader.Get(), const_cast<Texture *>(texture), GetFrame().GetTransform().GetMVP());
		}

		ImageView::ImageView(const Frame frame, const ImageViewFactory *factory, const std::string &image_name) :
		View(frame)
		{
			const TextureAtlasRegion region = factory->atlas.Get()->GetTextureAtlasRegion(image_name);
			vertex_ = new TextureVertex(region);
			render_object_ = new RenderObject(vertex_, factory->shader.Get(), factory->atlas.Get()->GetTexture(), frame.GetTransform().GetMVP());
		}
		
		ImageView::~ImageView(){
			if(vertex_) {
				delete vertex_;
			}
			delete render_object_;
		}
		
		void ImageView::update(float dt){
			render_object_->SetMVP(GetFrame().GetTransform().GetMVP());
			View::update(dt);
		}
		
		void ImageView::render(){
			render_object_->Render();
			View::render();
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

}/*namespace he*/

///EOF

