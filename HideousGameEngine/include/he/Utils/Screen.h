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

		Screen(const float width, const float height, const float z_min = 0.1f, const float z_max = 100.0f);
		void SetProjection(GLKMatrix4 projection = GLKMatrix4Identity);
		Grid MapPointToGrid(GLKVector2 point);
		
		const GLKVector2 GetSize() const;
		const GLKMatrix4 &GetProjection() const;
		const float GetHalfDepth() const;				/**< The halfway depth. Could be used for z-indexing. Always > 0 ( = -z_) */
		
		float width_;
		float height_;
		const float z_;								/**< z is midpoint of the total depth possible. Always < 0*/
		GLKMatrix4 projection_;
	};
	
	extern Screen* g_Screen;
}
#endif /* defined(__HideousGameEngine__Screen__) */
