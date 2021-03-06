//
//  ColorShader.h
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
 
#ifndef __HEAssets__ColorShader__
#define __HEAssets__ColorShader__
#include <string>

#include <OpenGLES/ES2/gl.h>

#include <he/Shaders/IShader.h>

namespace he{
	class Program;
	class RenderObject;
	
	class ColorShader : public IShader{
	public:
		ColorShader();
		~ColorShader();
		
	private:
		void render(const RenderObject *render_object) const;
		
		he::Program *program_;
		GLint a_position;
		GLint a_color;
		GLint u_mvp;
	};
}
#endif /* defined(__HEAssets__ColorShader__) */
