//
//  ColorShader.cpp
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
#include <he/Shaders/ColorShader.h>

#include <he/Program/Program.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Vertex/ColorVertex.h>

namespace he{
	ColorShader::ColorShader(){
		a_position = 0;
		std::map<std::string, GLint *>attribs;
		attribs["a_position"] = &a_position;
		
		std::map<std::string, GLint *>uniforms;
		uniforms["u_mvp"] = &u_mvp;
		uniforms["u_clr"] = &u_clr;
		
		program_ = new Program("ColorShader", BindAttrib(attribs),BindUniform(uniforms));
	}

	ColorShader::~ColorShader(){
		delete program_;
	}

	void ColorShader::Render(RenderObject *render_object){
		glUseProgram(program_->object_);
		
		glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 0, render_object->GetVertexData()->GetPositionData());
		glEnableVertexAttribArray(a_position);
		
		glUniform4f(u_clr, render_object->color_.r, render_object->color_.g, render_object->color_.b, render_object->color_.a);
		glUniformMatrix4fv(u_mvp, 1, GL_FALSE, render_object->mvp_.m);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, render_object->GetVertexData()->GetCount());
		
		glDisableVertexAttribArray(a_position);
		glUseProgram(0);
	}
}
