//
//  Sprite.cpp
//  HideousGameEngine
//
//  Created by Sid on 20/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/Sprite.h>
#include <he/Animation/AnimationLoop.h>
#include <he/Animation/SpriteAnimation.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Vertex/TextureVertex.h>
#include <he/Utils/Utils.h>

namespace he{ namespace ui{
	Sprite::Sprite(const ImageViewFactory *factory, const std::string &image_name, const Frame frame,
				   const int repeat_count, const int final_frame, const float fps) :
	ImageView(factory, FlashFullName(image_name), frame)
	{
		he::SpriteAnimation *animation = new he::SpriteAnimation(&vertex_, factory->atlas.Get(), image_name, repeat_count, final_frame, fps);
		assert(animation);
		
		he::g_AnimationLoop->AddAnimation(animation);
		
	}

	Sprite::~Sprite(){
		
	}
	
	void Sprite::update(float dt){
		render_object_->SetVertexData(vertex_);
		ImageView::update(dt);
	}
	
	void Sprite::render(){
		ImageView::render();
	}
} }
///EOF