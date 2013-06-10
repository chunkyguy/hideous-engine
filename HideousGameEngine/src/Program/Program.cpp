//
//  Program.cpp
//  HEAssets
//
//  Created by Sid on 19/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//


#include <fstream>

#include <he/Program/Program.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/DebugHelper.h>
#include <he/Utils/Utils.h>

namespace he{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Shader
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Shader{
	public:
		Shader(GLenum type, std::string &filename);
		~Shader();
		
		GLint object_;
	};
	
	Shader::Shader(GLenum type, std::string &filename) :
	object_(0)
	{
		//read code
		std::string	filePath = ResourcePath() + filename + (type == GL_VERTEX_SHADER?".vertsh":".fragsh");
		FileBuffer file(filePath);
		const char *codeBuffer = file.GetData();		
		//compile
		object_ = glCreateShader(type);
		assert(object_);
		
		glShaderSource(object_, 1, &codeBuffer,NULL);
		glCompileShader(object_);
		
		// check for errors
		GLint status;
		glGetShaderiv(object_, GL_COMPILE_STATUS, &status);
		if(status == GL_FALSE){
			GLint infologlen;
			glGetShaderiv(object_, GL_INFO_LOG_LENGTH, &infologlen);
			char *log = new char[infologlen + 1];
			glGetShaderInfoLog(object_, infologlen, NULL, log);
			std::string msg("Compilation fail: ");
			msg += log;
			delete[] log;
			glDeleteShader(object_);
			object_ = 0;
			he_Trace("%@ %@\n",filename, msg);
		}
	}

	Shader::~Shader(){
		if(object_){
			glDeleteShader(object_);
			object_ = 0;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Program
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Program::Program(std::string filename, BindAttrib b, BindUniform u) :
	object_(0)
	{
		Shader vsh(GL_VERTEX_SHADER, filename);;
		Shader fsh(GL_FRAGMENT_SHADER, filename);
		
		
		//link
		object_ = glCreateProgram();
		assert(object_);// "Unable to create program"
		glAttachShader(object_, vsh.object_);
		glAttachShader(object_, fsh.object_);
		b(object_);
		glLinkProgram(object_);
		u(object_);
		glDetachShader(object_, vsh.object_);
		glDetachShader(object_, vsh.object_);
		
		// check for error
		GLint status;
		glGetProgramiv(object_, GL_LINK_STATUS, &status);
		if(status == GL_FALSE){
			GLint infologlen;
			glGetProgramiv(object_, GL_INFO_LOG_LENGTH, &infologlen);
			char *log = new char[infologlen + 1];
			glGetProgramInfoLog(object_, infologlen, NULL, log);
			std::string msg("Linking error: ");
			msg += log;
			delete [] log;
			glDeleteProgram(object_);
			he_Trace("%@ %@\n",filename,msg);
		}
	}
	
	Program::~Program(){
		if(object_){
			glDeleteProgram(object_);
			object_ = 0;
		}
	}
}

///EOF
