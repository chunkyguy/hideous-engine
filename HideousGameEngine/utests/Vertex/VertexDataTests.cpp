//
//  VertexData.cpp
//  HEAssets
//
//  Created by Sid on 22/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Vertex/VertexData.h>
#include <he/Utils/Screen.h>

#include <gtest.h>
TEST(VertexData, Equality){
	he::Vertex::V2 a;
	he::Vertex::Set(a, GLKVector2Make(50, -100), GLKVector2Make(50, 100), GLKVector2Make(-50, -100), GLKVector2Make(-50, 100));

	he::Vertex::V2 b;
	he::Vertex::Set(b, GLKVector2Make(50, -100), GLKVector2Make(50, 100), GLKVector2Make(-50, -100), GLKVector2Make(-50, 100));

	ASSERT_TRUE(he::Vertex::Equal(a, b));
}

TEST(VertexData, GlobalTransformTranslate){
	he::g_Screen = new he::Screen(480, 320);
	
	he::Vertex::V2 start;
	he::Vertex::Set(start, GLKVector2Make(-100, -50), GLKVector2Make(100, 50));

	he::Vertex::V2 end;
	he::Vertex::Set(end, GLKVector2Make(0, 0), GLKVector2Make(200, 100));
	
	he::Transform global = he::Transform_Create(GLKVector2Make(-100, -50));
	he::Vertex::ApplyTransform(end, global);

	ASSERT_TRUE(he::Vertex::Equal(start, end));
	
	delete he::g_Screen;
}

TEST(VertexData, GlobalTransformRotate){
	he::g_Screen = new he::Screen(480, 320);
	
	he::Vertex::V2 start;
	he::Vertex::Set(start, GLKVector2Make(-100, -50), GLKVector2Make(100, 50));
	
	he::Vertex::V2 end;
	he::Vertex::Set(end, GLKVector2Make(50, -100), GLKVector2Make(50, 100), GLKVector2Make(-50, -100), GLKVector2Make(-50, 100));
	
	he::Transform global = he::Transform_Create(GLKVector2Make(0, 0), GLKVector4Make(0, 0, 1, GLKMathDegreesToRadians(90)));
	he::Vertex::ApplyTransform(start, global);
	
	ASSERT_TRUE(he::Vertex::Equal(start, end));
	
	delete he::g_Screen;
}

