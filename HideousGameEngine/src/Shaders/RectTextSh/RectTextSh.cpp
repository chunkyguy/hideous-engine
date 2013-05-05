//
//  RectTextSh.cpp
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <map>

#include <he/Program/Program.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/RectTextSh/RectTextSh.h>
#include <he/Texture/Texture.h>
#include <he/Vertex/VertexTex.h>

namespace he{
	
	RectTextSh::RectTextSh(){
		a_position = 0;
		a_texcoord = 1;
		std::map<std::string, GLint *> attribs;
		attribs["a_position"] = &a_position;
		attribs["a_texcoord"] = &a_texcoord;
		
		std::map<std::string, GLint *>uniforms;
		uniforms["u_mvp"] = &u_mvp;
		uniforms["u_tex"] = &u_tex;
		uniforms["u_clr"] = &u_clr;
		
		program_ = new Program("RectTextSh", BindAttrib(attribs),BindUniform(uniforms));
	}
	
	RectTextSh::~RectTextSh(){
		delete program_;
	}

	void RectTextSh::Render(RenderObject *render_object){
		VertexTex *vertex_data = static_cast<VertexTex *>(render_object->vertex_data_);
		
		glUseProgram(program_->object_);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, render_object->texture_->object_);
		
		glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 0, vertex_data->position_data_.GetData());
		glEnableVertexAttribArray(a_position);
		
		glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, 0, vertex_data->texture_data_.GetData());
		glEnableVertexAttribArray(a_texcoord);
		
		glUniform4f(u_clr, render_object->color_.r, render_object->color_.g, render_object->color_.b, render_object->color_.a);
		glUniformMatrix4fv(u_mvp, 1, GL_FALSE, render_object->mvp_.m);
		glUniform1i(u_tex, 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		
		glDisableVertexAttribArray(a_position);
		glDisableVertexAttribArray(a_texcoord);
		glUseProgram(0);
	}

}