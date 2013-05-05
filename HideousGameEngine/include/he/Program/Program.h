//
//  Program.h
//  HEAssets
//
//  Created by Sid on 19/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
 
#ifndef __HEAssets__Program__
#define __HEAssets__Program__

#include <string>
#include <map>
#include <OpenGLES/ES2/gl.h>

namespace he{
	
	
	//	Bind attrib callback
	class BindAttrib{
	public:
		BindAttrib(std::map<std::string, GLint *> &attributes) :
		attributes_(attributes)
		{}
		
		void operator()(GLint program){
			for(std::map<std::string, GLint *>::iterator it = attributes_.begin(); it != attributes_.end(); it++){
				glBindAttribLocation(program, *(it->second), it->first.c_str());
			}
		}
	private:
		std::map<std::string, GLint *> attributes_;
	};
	
	//	Bind uniform callback
	class BindUniform{
	public:
		BindUniform(std::map<std::string, GLint *> &uniforms) :
		uniforms_(uniforms)
		{}
		
		void operator()(GLint program){
			for(std::map<std::string, GLint *>::iterator it = uniforms_.begin(); it != uniforms_.end(); it++){
				*(it->second) = glGetUniformLocation(program, it->first.c_str());
			}
		}
	private:
		std::map<std::string, GLint *> uniforms_;
	};
	
	
	class Program{
	public:
		Program(std::string filename, BindAttrib attributes_map, BindUniform uniforms_map);
		~Program();
		
		GLint object_;
	};
}
#endif /* defined(__HEAssets__Program__) */
