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

namespace he{
	Sprite::Sprite(const Frame frame, const std::string &animation_name, const TextureShader *shader, const TextureAtlas *atlas,
				   const int repeat_count, const int final_frame, const float fps) :
	View(frame),
	vertex_(nullptr),
	render_object_()
	{
		he::SpriteAnimation *animation = new he::SpriteAnimation(&vertex_, atlas, animation_name, repeat_count, final_frame, fps);
		he::g_AnimationLoop->MoveAnimation(animation);
		assert(vertex_);		// There is some default vertex data.
		render_object_ = new RenderObject(vertex_, shader, atlas->GetTexture(), Transform_GetMVP(&(frame.GetTransform())));
	}
	
	Sprite::~Sprite(){
		if(vertex_) {
			delete vertex_;
		}
		delete render_object_;
	}
	
	void Sprite::update(float dt){
	}
	
	void Sprite::render(){
		render_object_->SetVertexData(vertex_);
		render_object_->SetMVP(Transform_GetMVP(&(GetFrame().GetTransform())));
		render_object_->Render();
	}
} 
///EOF