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
#include <he/Utils/DebugLog.h>
#include <he/Utils/DebugHelper.h>

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
		FILE_LOG(logDEBUG) << "Shader(): " << filePath;
		std::ifstream fin;
		fin.open(filePath.c_str());
		assert(fin.is_open());
		
		fin.seekg(0, std::ios::end);
		int len = fin.tellg();
		fin.seekg(0, std::ios::beg);
		char *codeBuffer = new char[len + 1];
		fin.read(codeBuffer, len);
		codeBuffer[len] = 0;
		
		//compile
		object_ = glCreateShader(type);
		assert(object_);
		
		glShaderSource(object_, 1, (const GLchar **)&codeBuffer,NULL);
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
			FILE_LOG(logERROR) << msg << std::endl;
		}
		delete codeBuffer;
	}

	Shader::~Shader(){
		FILE_LOG(logDEBUG) << "~Shader()";
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
		FILE_LOG(logDEBUG) << "Program()";
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
			std::string msg("Linking error");
			msg += log;
			delete [] log;
			glDeleteProgram(object_);
			FILE_LOG(logERROR) << msg << std::endl;
		}
	}
	
	Program::~Program(){
		FILE_LOG(logDEBUG) << "~Program()";
		if(object_){
			glDeleteProgram(object_);
			object_ = 0;
		}
	}
}

///EOF
