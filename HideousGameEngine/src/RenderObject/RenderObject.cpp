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
	RenderObject::RenderObject(IVertex *vertex_data, IShader *shader, Texture *texture, GLKMatrix4 mvp, GLKVector4 color) :
	vertex_data_(vertex_data),
	shader_(shader),
	texture_(texture),
	mvp_(mvp),
	color_(color)
	{	}
	
	void RenderObject::Render(){
		if(shader_){
			shader_->Render(this);
		}
	}
	
	void RenderObject::SetColor(const GLKVector4 &color){
		color_ = color;
	}
	GLKVector4 RenderObject::GetColor() const{
		return color_;
	}
	
	void RenderObject::SetMVP(const GLKMatrix4 &mvp){
		mvp_ = mvp;
	}
	GLKMatrix4 RenderObject::GetMVP() const{
		return mvp_;
	}
	
	void RenderObject::SetShader(IShader *shader){
		shader_ = shader;
	}
	IShader *RenderObject::GetShader() const{
		return shader_;
	}
	
	void RenderObject::SetTexture(Texture *texture){
		texture_ = texture;
	}
	Texture *RenderObject::GetTexture() const{
		return texture_;
	}
	
	void RenderObject::SetVertexData(IVertex *data){
		vertex_data_ = data;
	}
	IVertex *RenderObject::GetVertexData() const{
		return vertex_data_;
	}


}