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
#include <he/Texture/TextureAtlas.h>
#include <he/Shaders/TextureShader.h>
#include <he/Texture/Texture.h>
#include <he/Vertex/TextureVertex.h>
#include <he/Texture/TextureAtlasRegion.h>

namespace he{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Sprite
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Sprite::Sprite(const std::string &animation_name, const TextureShader *shader, const TextureAtlas *atlas,
				   const int repeat_count, const int final_frame, const float fps) :
	vertex_(nullptr),
	render_object_(),
	size_(atlas->GetTextureAtlasRegion(he::FlashFullName(animation_name)).sprite_size_)
	{
		he::SpriteAnimation *animation = new he::SpriteAnimation(&vertex_, atlas, animation_name, repeat_count, final_frame, fps);
		he::g_AnimationLoop->MoveAnimation(animation);
		assert(vertex_);		// There is some default vertex data.
		render_object_ = new RenderObject(vertex_, shader, atlas->GetTexture());
	}
	
	Sprite::~Sprite(){
		if(vertex_) {
			delete vertex_;
		}
		delete render_object_;
	}
	
	void Sprite::Render(const Transform &transform){
		render_object_->SetVertexData(vertex_);
		render_object_->SetMVP(Transform_GetMVP(&transform));
		render_object_->Render();
	}

	GLKVector2 Sprite::GetSize() const {
		return size_;
	}
	//Utility
	namespace sprite {
		Sprite *Create(const TextureShader *shader, const TextureAtlas *texture_atlas, const std::string &region_name,
					   const int repeat_count, const int final_frame, const float fps){
			return new Sprite(region_name, shader, texture_atlas, repeat_count, final_frame, fps);
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: SpriteView
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SpriteView::SpriteView(const Transform &transform, Sprite *sprite) :
	View(transform),
	sprite_(sprite)
	{}
	
	void SpriteView::Update(float dt) {
		View::Update(dt);
	}
	
	void SpriteView::Render() {
		sprite_->Render(GetTransform());
	}
	
	GLKVector2 SpriteView::GetSize() const {
		return sprite_->GetSize();
	}
} 
///EOF