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
	he::g_Screen = new he::Screen();

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
	he::g_Screen = new he::Screen();
	
	he::Frame view_frame;
	he::ui::View *view =  new he::ui::View(view_frame);

	he::Frame subvw_frame(he::Transform(GLKVector3Make(0.0f, 0.0f, 0.0f)));
	he::ui::View *subview = new he::ui::View(subvw_frame);
	view->AddSubview(subview);
	
	GLKVector2 new_pos = GLKVector2Make(100, 100);
	view->frame_.GetTransformPtr()->SetPosition(new_pos);
	
	view->Update(0.0);
	ASSERT_TRUE(view->frame_.GetTransform().GetMV() == subview->frame_.GetTransform().GetMV());
	delete view;
	delete he::g_Screen;
}