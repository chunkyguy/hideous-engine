//
//  RectTextureSh.cpp
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <map>

#include <he/Program/Program.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/RectTextureSh/RectTextureSh.h>
#include <he/Texture/Texture.h>
#include <he/Vertex/VertexTex.h>

namespace he{
	RectTextureSh::RectTextureSh(){
		a_position = 0;
		a_texcoord = 1;
		std::map<std::string, GLint *> attribs;
		attribs["a_position"] = &a_position;
		attribs["a_texcoord"] = &a_texcoord;
		
		std::map<std::string, GLint *>uniforms;
		uniforms["u_mvp"] = &u_mvp;
		uniforms["u_tex"] = &u_tex;
		
		program_ = new Program("RectTextureSh", BindAttrib(attribs),BindUniform(uniforms));
	}

	RectTextureSh::~RectTextureSh(){
		delete program_;
	}
	
	void RectTextureSh::Render(RenderObject *render_object){
		VertexTex *vertex_data = static_cast<VertexTex *>(render_object->vertex_data_);
		
		glUseProgram(program_->object_);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, render_object->texture_->object_);
		
		glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 0, vertex_data->position_data_.GetData());
		glEnableVertexAttribArray(a_position);
		
		glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, 0, vertex_data->texture_data_.GetData());
		glEnableVertexAttribArray(a_texcoord);
		
		glUniformMatrix4fv(u_mvp, 1, GL_FALSE, render_object->mvp_.m);
		glUniform1i(u_tex, 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		
		glDisableVertexAttribArray(a_position);
		glDisableVertexAttribArray(a_texcoord);
		glUseProgram(0);
	}
}