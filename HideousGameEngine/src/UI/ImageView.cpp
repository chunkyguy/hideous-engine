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

namespace he {
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ImageView
	///////////////////////////////////////////////////////////////////////////////////////////////////
	ImageView::ImageView(const Frame frame, const TextureVertex *vertex_m, const TextureShader *shader, const Texture *texture) :
	View(frame),
	vertex_(vertex_m),
	render_object_(new RenderObject(const_cast<TextureVertex *>(vertex_m), shader, const_cast<Texture *>(texture), Transform_GetMVP(&(frame.GetTransform()))))
	{}
	
	ImageView::~ImageView(){
		if(vertex_) {
			delete vertex_;
		}
		delete render_object_;
	}
	
	void ImageView::update(float dt){
	}
	
	void ImageView::render(){
		render_object_->SetMVP(Transform_GetMVP(&(GetFrame().GetTransform())));
		render_object_->Render();
	}
	
}/*namespace he*/

///EOF

