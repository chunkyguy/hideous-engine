//
//  TypesTests.cpp
//  HideousGameEngine
//
//  Created by Sid on 18/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/Types.h>

#include <gtest.h>

// These two should pass almost equal test.
TEST(Types, F32Equal){
	float a = 50;
	float b = 50.00000381;
	
	EXPECT_TRUE(he::F32Eq(a,b));
}