//
//  ParticleTest_2.cpp
//  HideousGameEngine
//
//  Created by Sid on 15/08/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "ParticleTest_2.h"

#include <map>
#include <he/Program/Program.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Texture/Texture.h>

namespace particle {
	/*******************************************************************************************************************************************
	 * MARK: ParticleShader
	 *******************************************************************************************************************************************/

	ParticleShader::ParticleShader() :
	a_position(0),
	a_color(0),
	a_size(0)
	{
		std::map<std::string, GLint *>attribs;
		attribs["a_position"] = &a_position;
		attribs["a_color"] = &a_color;
		attribs["a_size"] = &a_size;
		
		std::map<std::string, GLint *>uniforms;
		uniforms["u_mvp"] = &u_mvp;
		uniforms["u_tex"] = &u_tex;
		
		//		program_ = new he::Program("ParticleShader2", BindAttrib(attribs),BindUniform(uniforms));
	}
	
	ParticleShader::~ParticleShader() {
		delete program_;
	}

	void ParticleShader::render(const he::RenderObject *render_object) const {
//		assert(program_->object_);	// program prepared
//		assert(render_object->texture_->object_);	//texture prepared
//		assert(render_object->GetVertexData()->GetRawData(he::IVertex::kPosition)); // should have position data
//		
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//		
//		glUseProgram(program_->object_);
//		
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, render_object->texture_->object_);
//
//		ParticleVertex *vertex = (ParticleVertex*)(render_object->GetVertexData());
//		
//		//position
//		glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 0, vertex->GetRawData(ParticleVertex::kPosition));
//		glEnableVertexAttribArray(a_position);
//		//color
//		glVertexAttribPointer(a_color, 4, GL_FLOAT, GL_FALSE, 0, vertex->GetRawData(ParticleVertex::kColor));
//		glEnableVertexAttribArray(a_color);
//		//size
//		glVertexAttribPointer(a_size, 1, GL_FLOAT, GL_FALSE, 0, vertex->GetRawData(ParticleVertex::kTexture));
//		glEnableVertexAttribArray(a_size);
//		
//		
//		glUniform4f(u_clr, render_object->color_.r, render_object->color_.g, render_object->color_.b, render_object->color_.a);
//		glUniformMatrix4fv(u_mvp, 1, GL_FALSE, render_object->mvp_.m);
//		glUniform1i(u_tex, 1);
//		glUniform1f(u_size, static_cast<const ParticleVertex *>(render_object->GetVertexData())->GetPointSize());
//		
//		glDrawArrays(GL_POINTS, 0, render_object->GetVertexData()->GetCount());
//		
//		glDisableVertexAttribArray(a_position);
//		glUseProgram(0);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	
}