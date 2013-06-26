//
//  Transform.cpp
//  HideousGameEngine
//
//  Created by Sid on 06/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/Transform.h>
#include <he/Utils/DebugHelper.h>
#include <he/Utils/GLKMath_Additions.h>

#include <gtest.h>

TEST(Transform, Translate){
	he::Transform start = he::Transform_Create(GLKVector3Make(0, 0, 0));
	he::Transform end = he::Transform_Create(GLKVector3Make(100, 100, 0));

	start.position = GLKVector3Make(100, 100, start.position.z);
	
	ASSERT_TRUE(he::Transform_GetMV(&start) == he::Transform_GetMV(&end));
}

TEST(Transform, Rotate){
	he::Transform start = he::Transform_Create(GLKVector3Make(0, 0, 0), GLKVector4Make(0, 0, 1, 0));
	he::Transform end = he::Transform_Create(GLKVector3Make(0, 0, 0), GLKVector4Make(0, 0, 1, GLKMathDegreesToRadians(45)));
	
	start.rotation.w = GLKMathDegreesToRadians(45);
	he_Trace("Test:Transform:Rotate:\n%@\n",he::Transform_GetMV(&start));
	ASSERT_TRUE(he::Transform_GetMV(&start) == he::Transform_GetMV(&end));
}