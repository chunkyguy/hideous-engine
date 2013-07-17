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
#include <he/Utils/GLKMath_Additions.h>

namespace he{
	
	class Texture{
	public:
		Texture(std::string path, GLint align = 4);
		Texture(std::string path, GLubyte *data, GLKVector2 size, GLint align = 4);
		explicit Texture(Texture *texture);
		~Texture();
		GLKVector2 GetSize() const;
		
		GLuint object_;
		std::string path_;
		GLKVector2 size_;
		
	private:
		void load_texture(GLubyte *data, GLint align = 4);
		
		bool destructible_;	// in case of original texture
	};

}
#endif /* defined(__HideousGameEngine__Texture__) */
