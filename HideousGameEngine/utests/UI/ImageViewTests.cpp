//
//  ImageView.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <gtest.h>
#include <he/UI/ImageView.h>

#include <he/UI/ImageViewFactory.h>
#include <he/Utils/Screen.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Shaders/TextureShader.h>
#include <he/Utils/DebugHelper.h>
#include <he/Utils/Frame.h>

/** Test if creating view with another view's frame works */
TEST(ImageView, CreateViewWithImageViewsFrame){
	he::g_Screen = new he::Screen(480, 320);

	he::ImageViewFactory factory(nullptr, he::ResourcePath() + "ship_144.png");
	he::ImageView *img_vw = factory.CreateImageView(he::Transform_Create(GLKVector3Make(0, 50, 0)));

	he::Frame sub_frame1(he::Transform_Create(GLKVector3Make(0, 0, 0)), img_vw->GetFrame().GetSize());
	he::Frame sub_frame2 = CreateLocalFrame(img_vw->GetFrame());
	
	EXPECT_EQ(sub_frame1.GetRect(), sub_frame2.GetRect());
	delete img_vw;
}

