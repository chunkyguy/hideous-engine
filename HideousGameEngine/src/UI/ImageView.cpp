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
#include <he/Vertex/TextureVertex.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Texture/TextureAtlasRegion.h>

namespace he {
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Image
	///////////////////////////////////////////////////////////////////////////////////////////////////
	Image::Image(const TextureVertex *vertex_m, const TextureShader *shader, const Texture *texture) :
	vertex_(vertex_m),
	render_object_(new RenderObject(const_cast<TextureVertex *>(vertex_m), shader, const_cast<Texture *>(texture)))
	{}

	Image::~Image() {
		if(vertex_) {
			delete vertex_;
		}
		delete render_object_;
	}
	
	void Image::Render(const Frame &frame) {
		render_object_->SetMVP(Transform_GetMVP(&(frame.GetTransform())));
		render_object_->Render();
	}

	// Utility
	namespace image {
		Image *Create(const TextureShader *shader, const Texture *texture) {
			return new Image(new TextureVertex(texture->GetSize()), shader, texture);
		}
		Image *Create(const TextureShader *shader, const TextureAtlas *texture_atlas, const std::string &region_name) {
			const TextureAtlasRegion region = texture_atlas->GetTextureAtlasRegion(region_name);
			return new Image(new TextureVertex(region), shader, texture_atlas->GetTexture());
		}
	}

	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ImageView
	///////////////////////////////////////////////////////////////////////////////////////////////////
	ImageView::ImageView(const Frame frame, Image *image) :
	View(frame),
	image_(image)
	{}
	
	ImageView::~ImageView() {
	}
	
	void ImageView::Update(float dt) {
		View::Update(dt);
	}
	
	void ImageView::Render(){
		image_->Render(GetFrame());

		View::Render();
	}
	
}/*namespace he*/

///EOF

