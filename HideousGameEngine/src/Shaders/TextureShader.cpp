//
//  TextureShader.cpp
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
#include <he/Shaders/TextureShader.h>

#include <map>

#include <he/Program/Program.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Texture/Texture.h>
#include <he/Vertex/TextureVertex.h>

namespace he{
	TextureShader::TextureShader(){
		a_position = 0;
		a_texcoord = 1;
		std::map<std::string, GLint *> attribs;
		attribs["a_position"] = &a_position;
		attribs["a_texcoord"] = &a_texcoord;
		
		std::map<std::string, GLint *>uniforms;
		uniforms["u_mvp"] = &u_mvp;
		uniforms["u_tex"] = &u_tex;
		
		program_ = new Program("TextureShader", BindAttrib(attribs),BindUniform(uniforms));
	}

	TextureShader::~TextureShader(){
		delete program_;
	}
	
	void TextureShader::Render(RenderObject *render_object){
		assert(program_->object_);	// program prepared
		assert(render_object->texture_->object_);	//texture prepared
		assert(render_object->GetVertexData()->GetRawData(IVertex::kPosition)); // should have position data
		assert(render_object->GetVertexData()->GetRawData(IVertex::kTexture));	// should have texture data
		assert(render_object->GetVertexData()->GetCount() > 3);	//atleast 4 vertices needed to render a quad

		glUseProgram(program_->object_);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, render_object->texture_->object_);
		
		glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 0, render_object->GetVertexData()->GetRawData(IVertex::kPosition));
		glEnableVertexAttribArray(a_position);
		
		glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, 0, render_object->GetVertexData()->GetRawData(IVertex::kTexture));
		glEnableVertexAttribArray(a_texcoord);
		
		glUniformMatrix4fv(u_mvp, 1, GL_FALSE, render_object->mvp_.m);
		glUniform1i(u_tex, 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, render_object->GetVertexData()->GetCount());
		
		glDisableVertexAttribArray(a_position);
		glDisableVertexAttribArray(a_texcoord);
		glUseProgram(0);
	}
}