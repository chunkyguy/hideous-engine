//
//  Texture.h
//  HideousGameEngine
//
//  Created by Sid on 24/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
 
#ifndef __HideousGameEngine__Texture__
#define __HideousGameEngine__Texture__
#include <OpenGLES/ES2/gl.h>
#include <string>
#include <GLKit/GLKMath.h>

namespace he{
	
	class Texture{
	public:
		Texture(std::string name, std::string extension, GLint align = 4);
		Texture(std::string name, std::string extension, GLubyte *data, GLKVector2 size, GLint align = 4);
		explicit Texture(Texture *texture);
		~Texture();
		
		std::string name_;
		std::string extension_;
		GLuint object_;
		
	private:
		void load_texture(GLubyte *data, GLKVector2 size, GLint align = 4);
		
		bool destructible_;	// in case of original texture
	};

}
#endif /* defined(__HideousGameEngine__Texture__) */
