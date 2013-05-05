//
//  Utils.h
//  HideousGameEngine
//
//  Created by Sid on 13/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
//	General Utilities inline functions
#ifndef __HideousGameEngine__Utils__
#define __HideousGameEngine__Utils__

#include <OpenGLES/ES2/gl.h>
#include <cstdlib>
#include <GLKit/GLKMath.h>

#include <he/Utils/Screen.h>

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
TypeName(const TypeName&);               \
void operator=(const TypeName&)

namespace he{
	// buffer offset calc for VBO data stride
	inline const GLvoid *BufferOffset(int off){
		return static_cast<char *>(0) + off;
	}
	
	// next power of 2
	int NextPOT(int a);
	
	//Returns a value between [0.0, 1.0]
	inline double Randf(){
		return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
	}
	
	//	Convert point from CoreGraphics coordinates space to OpenGL coordinate space
	inline GLKVector2 CGtoGL(GLKVector2 cg_point){
		return GLKVector2Make(cg_point.x - g_Screen.width_/2, g_Screen.height_/2 - cg_point.y);
	}

}
#endif /* defined(__HideousGameEngine__Utils__) */
