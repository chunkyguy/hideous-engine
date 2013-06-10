//
//  TextShader.cpp
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
#include <he/Shaders/TextShader.h>

#include <map>

#include <he/Program/Program.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Texture/Texture.h>
#include <he/Vertex/TextureVertex.h>

namespace he{
	
	TextShader::TextShader(){
		a_position = 0;
		a_texcoord = 1;
		std::map<std::string, GLint *> attribs;
		attribs["a_position"] = &a_position;
		attribs["a_texcoord"] = &a_texcoord;
		
		std::map<std::string, GLint *>uniforms;
		uniforms["u_mvp"] = &u_mvp;
		uniforms["u_tex"] = &u_tex;
		uniforms["u_clr"] = &u_clr;
		
		program_ = new Program("TextShader", BindAttrib(attribs),BindUniform(uniforms));
	}
	
	TextShader::~TextShader(){
		delete program_;
	}

	void TextShader::Render(RenderObject *render_object){
		
		glUseProgram(program_->object_);
		
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, render_object->texture_->object_);
		
		glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 0, render_object->GetVertexData()->GetPositionData());
		glEnableVertexAttribArray(a_position);
		
		glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, 0, render_object->GetVertexData()->GetTextureData());
		glEnableVertexAttribArray(a_texcoord);
		
		glUniform4f(u_clr, render_object->color_.r, render_object->color_.g, render_object->color_.b, render_object->color_.a);
		glUniformMatrix4fv(u_mvp, 1, GL_FALSE, render_object->mvp_.m);
		glUniform1i(u_tex, 2);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, render_object->GetVertexData()->GetCount());
		
		glDisableVertexAttribArray(a_position);
		glDisableVertexAttribArray(a_texcoord);
		glUseProgram(0);
	}

}