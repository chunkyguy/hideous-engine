//
//  GObj.h
//  HideousGameEngine
//
//  Created by Sid on 25/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__GObj__
#define __HideousGameEngine__GObj__

#include <he/Utils/Screen.h>
#include <he/Utils/Transform.h>

namespace he{
	class RenderObject;
	class VertexCol;
	class RectColorSh;
}

class GObj{
public:
	~GObj();
	GObj();
	void Update(double dt);
	void Render();
	void SetTransform(he::Transform tranform);
	void SetColor(GLKVector4 new_color);
	void SetDirection(he::Screen::Grid direction);
	
private:
	const double kSpeed = 1.0;

	he::RenderObject *render_object_;
	he::VertexCol *vert_;
	he::RectColorSh *shader_;
	he::Transform transform_;
	GLKVector4 color_;
	GLKVector2 direction_;
};
#endif /* defined(__HideousGameEngine__GObj__) */
