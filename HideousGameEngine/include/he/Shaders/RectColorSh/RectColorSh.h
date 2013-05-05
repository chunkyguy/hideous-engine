//
//  RectColorSh.h
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HEAssets__RectColorSh__
#define __HEAssets__RectColorSh__
#include <OpenGLES/ES2/gl.h>
#include <string>

#include <he/Shaders/IShader.h>

namespace he{
	class Program;
	class RenderObject;
	
	class RectColorSh : public IShader{
	public:
		RectColorSh();
		~RectColorSh();
		void Render(RenderObject *render_object);
		
		he::Program *program_;
		GLint a_position;
		GLint u_mvp;
		GLint u_clr;
	};
}
#endif /* defined(__HEAssets__RectColorSh__) */
