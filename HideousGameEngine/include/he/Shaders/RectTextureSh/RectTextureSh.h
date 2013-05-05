//
//  RectTextureSh.h
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HEAssets__RectTextureSh__
#define __HEAssets__RectTextureSh__
#include <OpenGLES/ES2/gl.h>
#include <string>

#include <he/Shaders/IShader.h>

namespace he{
	class Program;
	class RenderObject;
	
	class RectTextureSh : public IShader{
	public:
		~RectTextureSh();
		RectTextureSh();
		void Render(RenderObject *render_object);
		
		he::Program *program_;
		GLint a_position;
		GLint a_texcoord;
		GLint u_mvp;
		GLint u_tex;
	};
}
#endif /* defined(__HEAssets__RectTextureSh__) */
