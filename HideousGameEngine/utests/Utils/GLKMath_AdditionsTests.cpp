//
//  GLKMath_Additions.cpp
//  HideousGameEngine
//
//  Created by Sid on 08/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/GLKMath_Additions.h>

#include <gtest.h>

TEST(GLKVector2, Equality){
	GLKVector2 a = GLKVector2Make(0.5f, 0.5f);
	GLKVector2 b = GLKVector2Make(0.5f, 0.5f);
	EXPECT_TRUE(a == b);
}

TEST(GLKVector2, AlmostEquality){
	GLKVector2 a = GLKVector2Make(0.5f, 0.5f);
	GLKVector2 b = GLKVector2Make(0.5000001f, 0.5000001f);
	EXPECT_TRUE(a == b);
}

TEST(GLKVector3, Equality){
	GLKVector3 a = GLKVector3Make(0.5f, 0.5f, 0.5f);
	GLKVector3 b = GLKVector3Make(0.5f, 0.5f, 0.5f);
	EXPECT_TRUE(a == b);
}

TEST(GLKVector3, AlmostEquality){
	GLKVector3 a = GLKVector3Make(0.5f, 0.5f, 0.5f);
	GLKVector3 b = GLKVector3Make(0.5000001f, 0.5000001f, 0.5000001f);
	EXPECT_TRUE(a == b);
}

TEST(GLKVector4, Equality){
	GLKVector4 a = GLKVector4Make(0.5f, 0.5f, 0.5f, 0.5f);
	GLKVector4 b = GLKVector4Make(0.5f, 0.5f, 0.5f, 0.5f);
	EXPECT_TRUE(a == b);
}

TEST(GLKVector4, AlmostEquality){
	GLKVector4 a = GLKVector4Make(0.5f, 0.5f, 0.5f, 0.5f);
	GLKVector4 b = GLKVector4Make(0.5000001f, 0.5000001f, 0.5000001f, 0.5000001f);
	EXPECT_TRUE(a == b);
}


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