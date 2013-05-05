//
//  ParticleShader.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
#include <he/Program/Program.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/ParticleSh/ParticleSh.h>
#include <he/Texture/Texture.h>
#include <he/Vertex/VertexPar.h>

namespace he{

	ParticleSh::ParticleSh() :
	a_position(0)
	{
		std::map<std::string, GLint *>attribs;
		attribs["a_position"] = &a_position;
		
		std::map<std::string, GLint *>uniforms;
		uniforms["u_mvp"] = &u_mvp;
		uniforms["u_clr"] = &u_clr;
		uniforms["u_tex"] = &u_tex;
		uniforms["u_size"] = &u_size;
		uniforms["u_mvp"] = &u_mvp;
		
		program_ = new Program("ParticleSh", BindAttrib(attribs),BindUniform(uniforms));
	}

	ParticleSh::~ParticleSh(){
		delete program_;
	}

	void ParticleSh::Render(RenderObject *render_object){
		VertexPar *vertex_data = static_cast<VertexPar *>(render_object->vertex_data_);

		glUseProgram(program_->object_);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, render_object->texture_->object_);

		glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 0, vertex_data->position_data_.GetData());
		glEnableVertexAttribArray(a_position);


		glUniform4f(u_clr, render_object->color_.r, render_object->color_.g, render_object->color_.b, render_object->color_.a);
		glUniformMatrix4fv(u_mvp, 1, GL_FALSE, render_object->mvp_.m);
		glUniform1i(u_tex, 0);
		glUniform1f(u_size, vertex_data->point_size_);
		
		glDrawArrays(GL_POINTS, 0, vertex_data->count_);
	}
}
