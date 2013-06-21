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
	he::Frame view_frame;
	he::ui::View *view =  new he::ui::View(view_frame);
	view->AddSubview(new he::ui::View(view_frame));
	delete view;
	ASSERT_TRUE(1);
	delete he::g_Screen;
}


/** Test if updating a view's transfrom updates its child as well
 */
TEST(View, SubviewUpdate){
	he::g_Screen = new he::Screen(480, 320);
	
	he::Frame view_frame;
	he::ui::View *view =  new he::ui::View(view_frame);

	he::Frame subvw_frame(he::Transform(GLKVector3Make(0.0f, 0.0f, 0.0f)));
	he::ui::View *subview = new he::ui::View(subvw_frame);
	view->AddSubview(subview);

	he_Trace("1 One:\n%@\nTwo:\n%@\n",view->GetFrame().GetTransform().GetMVP(), subview->GetFrame().GetTransform().GetMVP());

	he::Frame new_frame(he::Transform(GLKVector3Make(100.0f, 100.0f, he::g_Screen->z_)));
	view->SetFrame(new_frame);
//	GLKVector2 new_pos = GLKVector2Make(100, 100);
//	view->GetFrame().GetTransformPtr()->SetPosition(new_pos);
	
	view->Update(0.0);
	he_Trace("2 One:\n%@\nTwo:\n%@\n",view->GetFrame().GetTransform().GetMVP(), subview->GetFrame().GetTransform().GetMVP());
	ASSERT_TRUE(view->GetFrame().GetTransform().GetMVP() == subview->GetFrame().GetTransform().GetMVP());
	delete view;
	delete he::g_Screen;
}