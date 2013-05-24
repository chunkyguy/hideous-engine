//
//  Screen.h
//  HideousGameEngine
//
//  Created by Sid on 10/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

//	Keep screen dimensions.

#ifndef __HideousGameEngine__Screen__
#define __HideousGameEngine__Screen__
#include <he/Utils/GLKMath_Additions.h>

namespace he{
	//Dividing the Screen into a rect of 3x3, with key mapping as
	//	-------------------------
	//	|	TL	|	T	|	TR	|
	//	-------------------------
	//	|	L	|	C	|	R	|
	//	-------------------------
	//	|	BL	|	B	|	BR	|
	//	-------------------------
	
	class Screen{
	public:
		typedef enum{
			kTopLeft, kTop, kTopRight,
			kLeft, kCenter, kRight,
			kBottomLeft, kBottom, kBottomRight,
			kUnknown
		}Grid;

		Screen(double width = 0.0, double height = 0.0);
		void SetProjection(GLKMatrix4 projection = GLKMatrix4Identity);
		Grid MapPointToGrid(GLKVector2 point);
		
		double width_;
		double height_;
		GLKMatrix4 projection_;
	};
	
	extern Screen* g_Screen;
}
#endif /* defined(__HideousGameEngine__Screen__) */
