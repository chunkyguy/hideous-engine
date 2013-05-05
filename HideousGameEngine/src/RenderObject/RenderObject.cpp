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
}