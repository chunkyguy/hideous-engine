//
//  TextureCreator.h
//  HideousGameEngine
//
//  Created by Sid on 11/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

//	Helper class to create a texture using Quartz
#ifndef __HideousGameEngine__TextureCreator__
#define __HideousGameEngine__TextureCreator__
#include <OpenGLES/ES2/gl.h>
#include <string>
namespace he{
	
	class TextureData{
	public:
		TextureData(std::string &name, std::string extension);
		~TextureData();
		
		GLuint width_;
		GLuint height_;
		GLubyte *data_;
	};	
}
#endif
