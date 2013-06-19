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
#include <he/Utils/DebugHelper.h>

namespace he{
	ColorShader::ColorShader(){
		a_position = 0;
		a_color = 1;
		std::map<std::string, GLint *>attribs;
		attribs["a_position"] = &a_position;
		attribs["a_color"] = &a_color;
		
		std::map<std::string, GLint *>uniforms;
		uniforms["u_mvp"] = &u_mvp;
		
		program_ = new Program("ColorShader", BindAttrib(attribs),BindUniform(uniforms));
	}

	ColorShader::~ColorShader(){
		delete program_;
	}

	void ColorShader::Render(RenderObject *render_object){
		assert(program_->object_);	// program prepared
		assert(render_object->GetVertexData()->GetRawData(IVertex::kPosition)); // should have position data
		assert(render_object->GetVertexData()->GetRawData(IVertex::kColor));	// should have color data
		assert(render_object->GetVertexData()->GetCount() > 3);	//atleast 4 vertices needed to render a quad

		glUseProgram(program_->object_);
		
		glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 0, render_object->GetVertexData()->GetRawData(IVertex::kPosition));
		glEnableVertexAttribArray(a_position);
		glVertexAttribPointer(a_color, 4, GL_FLOAT, GL_FALSE, 0, render_object->GetVertexData()->GetRawData(IVertex::kColor));
		glEnableVertexAttribArray(a_color);
		
		glUniformMatrix4fv(u_mvp, 1, GL_FALSE, render_object->mvp_.m);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, render_object->GetVertexData()->GetCount());
		
		glDisableVertexAttribArray(a_position);
		glDisableVertexAttribArray(a_color);
		glUseProgram(0);
	}
}
