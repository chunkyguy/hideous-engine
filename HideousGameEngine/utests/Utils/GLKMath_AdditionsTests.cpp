//
//  GLKMath_Additions.cpp
//  HideousGameEngine
//
//  Created by Sid on 08/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/GLKMath_Additions.h>

#include <gtest.h>

TEST(GLKMatrix4, Equality){
	GLKMatrix4 a = GLKMatrix4MakeXRotation(1);
	GLKMatrix4 b = GLKMatrix4MakeXRotation(1);
	EXPECT_TRUE(a == b);
}

TEST(GLKMatrix4, TransformIdentity){
	GLKVector3 trans_vec = GLKVector3Make(14, 25, 36);
	GLKMatrix4 a = GLKMatrix4MakeTranslation(trans_vec.x, trans_vec.y, trans_vec.z);
	GLKMatrix4 b = GLKMatrix4Translate(GLKMatrix4Identity, trans_vec.x, trans_vec.y, trans_vec.z);
	EXPECT_TRUE(a == b);
}