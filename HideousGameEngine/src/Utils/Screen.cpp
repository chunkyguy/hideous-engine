//
//  Screen.cpp
//  HideousGameEngine
//
//  Created by Sid on 10/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/Screen.h>

namespace he{
	Screen* g_Screen = nullptr;
	
	Screen::Screen(float width, float height) :
	width_(width),
	height_(height)
	{
		projection_ = GLKMatrix4MakeOrtho(-width_/2, width_/2, -height_/2, height_/2, 0.1, 100.0);
	}

	void Screen::SetProjection(GLKMatrix4 projection){
		projection_ = projection;
	}

	const GLKVector2 Screen::GetSize() const{
		return GLKVector2Make(width_, height_);
	}
	
	const GLKMatrix4 &Screen::GetProjection() const{
		return projection_;
	}
	
	Screen::Grid Screen::MapPointToGrid(GLKVector2 point){
		float scr_w_one_third = width_/3;
		float scr_h_one_third = height_/3;
		int touch_index_x = point.x/scr_w_one_third;
		int touch_index_y = point.y/scr_h_one_third;
		
		if(touch_index_x < 3 && touch_index_y < 3){
			
			Grid g[3][3] = {
				{kTopLeft, kLeft, kBottomLeft},
				{kTop, kCenter, kBottom},
				{kTopRight, kRight, kBottomRight},
			};
			
			return g[touch_index_x][touch_index_y];
		}
		return kUnknown;
	}
}
//EOF