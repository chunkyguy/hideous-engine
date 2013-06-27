//
//  ParticleShader.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

// Directly coupled with Shader code.
 
#ifndef ParticleSystem_ParticleShader_h
#define ParticleSystem_ParticleShader_h

#include <he/Utils/GLKMath_Additions.h>
#include <OpenGLES/ES2/gl.h>

#include <he/Shaders/IShader.h>

namespace he{
	class Program;
	class RenderObject;
	
	class ParticleShader : public IShader{
	public:
		ParticleShader();
		~ParticleShader();
		
	private:
		void render(const RenderObject *render_object) const;
		
		Program *program_;
		//Attribs
		GLint a_position;
		//Uniforms
		GLint u_mvp;
		GLint u_size;
		GLint u_clr;
		GLint u_tex;
	};
}
#endif
