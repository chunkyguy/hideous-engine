//
//  Frame.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/Frame.h>

#include <gtest.h>

TEST(Frame, Equality){
	he::Frame fr;
	EXPECT_TRUE(he::Vertex::Equal(fr.GetRect(), fr.GetRect()));
}
