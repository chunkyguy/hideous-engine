//
//  GLKVector2_Additions.h
//  HideousGameEngine
//
//  Created by Sid on 16/05/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_GLKVector2_Additions_h
#define HideousGameEngine_GLKVector2_Additions_h
#include <GLKit/GLKMathTypes.h>

static inline GLKVector2 GLKMatrix2Multiply(GLKMatrix2 matrix, GLKVector2 vec){
	return GLKVector2Make(vec.x * matrix.m00 + vec.y * matrix.m01,
						  vec.x * matrix.m10 + vec.y * matrix.m11);
}


#endif
