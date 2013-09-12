//
//  ParticleTest_2.h
//  HideousGameEngine
//
//  Created by Sid on 15/08/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__ParticleTest_2__
#define __HideousGameEngine__ParticleTest_2__

#include <OpenGLES/ES2/gl.h>
#include <he/Utils/GLKMath_Additions.h>
#include <he/Shaders/IShader.h>
#include <he/Vertex/IVertex.h>
#include <he/Main/HideousGame.h>

namespace he {
	class Program;
}

namespace particle {
	/*******************************************************************************************************************************************
	 * MARK: ParticleShader
	 *******************************************************************************************************************************************/

	class ParticleShader : public he::IShader{
	public:
		ParticleShader();
		~ParticleShader();
		
	private:
		void render(const he::RenderObject *render_object) const;
		
		he::Program *program_;
		
		//Attribs
		GLint a_position;
		GLint a_color;
		GLint a_size;
		//Uniforms
		GLint u_mvp;
		GLint u_tex;
	};


	/*******************************************************************************************************************************************
	 * MARK: ParticleVertex
	 *******************************************************************************************************************************************/
	class ParticleVertex : public he::IVertex{
	public:

		~ParticleVertex();
		ParticleVertex(int count);
		void SetData(int index, const GLKVector2 &data);
		GLsizei GetSize() const;
		
	private:
		virtual const GLfloat *raw_data(const DataType dt) const;
		
		GLfloat *data_;
		GLsizei size_;
		float point_size_;
	};


	/*******************************************************************************************************************************************
	 * MARK: ParticleTest
	 *******************************************************************************************************************************************/
	class ParticleTest : public he::Game{
	public:
		~ParticleTest();
		ParticleTest();
		
	private:
		virtual void init();
		virtual void update(float dt);
		virtual void render();
	};
}


#endif /* defined(__HideousGameEngine__ParticleTest_2__) */
