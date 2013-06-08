//
//  FlashMovie.cpp
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "FlashMovie.h"

#include <he/Animation/AnimationLoop.h>
#include <he/Animation/SpriteAnimation.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/RectTextureSh/RectTextureSh.h>
#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Utils/DebugHelper.h>
#include <he/Utils/Screen.h>
#include <he/Vertex/VertexTex.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: FlashMovie
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlashMovie::FlashMovie(const std::string &name, const FlashMovieAssets *assets, const int final_frame, const float fps) :
vertex_data_(nullptr)
{

	he::RectTextureSh *sh = const_cast<he::RectTextureSh *>(assets->GetShader());
	assert(sh);
	
	he::Texture *tx = assets->GetAtlas()->GetTexture();
	assert(tx);
	
	GLKMatrix4 tMat = GLKMatrix4MakeTranslation(0, 0, -0.1);
	GLKMatrix4 mvpMat = GLKMatrix4Multiply(he::g_Screen->projection_, tMat);
	render_object_ = new he::RenderObject(vertex_data_, sh, tx, mvpMat);
	assert(render_object_);
	
	he::SpriteAnimation *animation = new he::SpriteAnimation(&vertex_data_, assets->GetAtlas(), name, final_frame, fps);
	assert(animation);
	
	he::g_AnimationLoop->AddAnimation(animation);
}

FlashMovie::~FlashMovie(){
	if(vertex_data_){
		delete vertex_data_;
	}
	delete render_object_;
}

void FlashMovie::Update(double dt){
	render_object_->SetVertexData(vertex_data_);
}

void FlashMovie::Render(){
	he::VertexTex *v = dynamic_cast<he::VertexTex *>(render_object_->GetVertexData());
	assert(v);
	render_object_->Render();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: FlashMovieAssets
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlashMovieAssets::FlashMovieAssets(he::TextureAtlas *atlas, he::RectTextureSh *shader) :
atlas_(atlas),
shader_(shader)
{}

FlashMovieAssets::~FlashMovieAssets(){
	delete atlas_;
	delete shader_;
}


const he::TextureAtlas *FlashMovieAssets::GetAtlas() const{
	return atlas_;
}

const he::RectTextureSh *FlashMovieAssets::GetShader() const{
	return shader_;
}
/// EOF
