//
//  View.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/View.h>
#include <he/Utils/Screen.h>

#include <gtest.h>

/** Test if the destructor cleans up the memory well
 */
TEST(View, Destructor){
	he::g_Screen = new he::Screen(480, 320);

	// load view
	he::Frame view_frame(he::Transform_Create(GLKVector3Make(0.0f, 0.0f, 0.0f)));
	he::View *view =  new he::View(view_frame);
	view->MoveSubview(new he::View(view_frame));
	delete view;
	ASSERT_TRUE(1);
	delete he::g_Screen;
}


/** Test if updating a view's transfrom updates its child as well
 */
TEST(View, SubviewUpdate){
	he::g_Screen = new he::Screen(480, 320);
	
	he::Frame view_frame(he::Transform_Create(GLKVector3Make(0.0f, 0.0f, 0.0f)));
	he::View *view =  new he::View(view_frame);

	he::Frame subvw_frame(he::Transform_Create(GLKVector3Make(0.0f, 0.0f, 0.0f)));
	he::View *subview = new he::View(subvw_frame);
	view->MoveSubview(subview);

	//he_Trace("1 One:\n%@\nTwo:\n%@\n",he::Transform_GetMVP(&(view->GetFrame().GetTransform())), he::Transform_GetMVP(&(subview->GetFrame().GetTransform())));

	he::Frame new_frame(he::Transform_Create(GLKVector2Make(100.0f, 100.0f)));
	view->SetFrame(new_frame);
//	GLKVector2 new_pos = GLKVector2Make(100, 100);
//	view->GetFrame().GetTransformPtr()->SetPosition(new_pos);
	
	view->Update(0.0);
	//he_Trace("2 One:\n%@\nTwo:\n%@\n",he::Transform_GetMVP(&(view->GetFrame().GetTransform())), he::Transform_GetMVP(&(subview->GetFrame().GetTransform())));

	ASSERT_TRUE(he::Transform_GetMVP(&(view->GetFrame().GetTransform())) == he::Transform_GetMVP(&(subview->GetFrame().GetTransform())));
	delete view;
	delete he::g_Screen;
}

/** Test if creating view with another view's frame works */
TEST(View, CreateViewWithAnotherViewsFrame){
	he::g_Screen = new he::Screen(480, 320);
	
	he::Frame view_frame(he::Transform_Create(GLKVector3Make(0.0f, 0.0f, 0.0f)));
	he::View *view =  new he::View(view_frame);
	
	he::Frame sub_frame1(he::Transform_Create(GLKVector3Make(0, 0, 0)), view->GetFrame().GetSize());
	he::View *sub_view1 = new he::View(sub_frame1);

	he::View *sub_view2 = new he::View(view->GetFrame());
	
	EXPECT_EQ(sub_view1->GetFrame().GetGlobalRect(), sub_view2->GetFrame().GetGlobalRect());
}
