//
//  RenderObject.cpp
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/IShader.h>
#include <he/Texture/Texture.h>
#include <he/Vertex/IVertex.h>

namespace he{
	RenderObject::RenderObject(const IVertex *vertex_data, const IShader *shader, const Texture *texture, const GLKMatrix4 mvp, const GLKVector4 color) :
	vertex_data_(vertex_data),
	shader_(shader),
	texture_(texture),
	mvp_(mvp),
	color_(color)
	{	}
	
	void RenderObject::Render() const{
		if(shader_){
			shader_->Render(this);
		}
	}
	
	void RenderObject::SetColor(const GLKVector4 &color){
		color_ = color;
	}
	const GLKVector4 RenderObject::GetColor() const{
		return color_;
	}
	
	void RenderObject::SetMVP(const GLKMatrix4 &mvp){
		mvp_ = mvp;
	}
	const GLKMatrix4 RenderObject::GetMVP() const{
		return mvp_;
	}
	
	void RenderObject::SetShader(const IShader *shader){
		shader_ = shader;
	}
	const IShader *RenderObject::GetShader() const{
		return shader_;
	}
	
	void RenderObject::SetTexture(const Texture *texture){
		texture_ = texture;
	}
	const Texture *RenderObject::GetTexture() const{
		return texture_;
	}
	
	void RenderObject::SetVertexData(const IVertex *data){
		vertex_data_ = data;
	}
	const IVertex *RenderObject::GetVertexData() const{
		return vertex_data_;
	}
}