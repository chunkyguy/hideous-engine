//
//  Frame.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/Frame.h>
#include <he/Utils/Screen.h>

#include <gtest.h>

TEST(Frame, Equality){
	he::g_Screen = new he::Screen(480, 320);
	he::Frame fr(he::Transform_Create(GLKVector3Make(0.0f, 0.0f, 0.0f)));
	EXPECT_EQ(fr.GetRect(), fr.GetRect());
	delete he::g_Screen;
}
