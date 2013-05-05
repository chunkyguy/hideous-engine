//
//  GLState.cpp
//  HEAssets
//
//  Created by Sid on 24/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
#include <OpenGLES/ES2/gl.h>

#include <he/Utils/GLState.h>

namespace he{
	void SetDefaultState(){
		
		glEnable(GL_TEXTURE_2D);
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glDisable(GL_DEPTH_TEST);
	}
}