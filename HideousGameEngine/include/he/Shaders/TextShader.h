//
//  TextShader.h
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
 
#ifndef __HEAssets__TextShader__
#define __HEAssets__TextShader__
#include <OpenGLES/ES2/gl.h>
#include <string>

#include <he/Shaders/IShader.h>

namespace he{
	class Program;
	class RenderObject;

	class TextShader : public IShader{
	public:
		
		TextShader();
		~TextShader();
		void Render(RenderObject *render_object);
		
		he::Program *program_;
		GLint a_position;
		GLint a_texcoord;
		GLint u_mvp;
		GLint u_tex;
		GLint u_clr;

	};
}
#endif /* defined(__HEAssets__TextShader__) */
