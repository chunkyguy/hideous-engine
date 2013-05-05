//
//  Screen.cpp
//  HideousGameEngine
//
//  Created by Sid on 10/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/Screen.h>

namespace he{
	Screen g_Screen;
	
	Screen::Screen(double width, double height) :
	width_(width),
	height_(height)
	{
		projection_ = GLKMatrix4MakeOrtho(-width_/2, width_/2, -height_/2, height_/2, 0.1, 100.0);
	}

	void Screen::SetProjection(GLKMatrix4 projection){
		projection_ = projection;
	}
	
	Screen::Grid Screen::MapPointToGrid(GLKVector2 point){
		double scr_w_one_third = width_/3;
		double scr_h_one_third = height_/3;
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