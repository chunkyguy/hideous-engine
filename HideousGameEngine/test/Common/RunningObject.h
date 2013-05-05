//
//  RunningObject.h
//  HEAssets
//
//  Created by Sid on 28/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HEAssets__RunningObject__
#define __HEAssets__RunningObject__

#include <GLKit/GLKMath.h>

namespace he{
	class RenderObject;
}

class RunningObject{
public:
	RunningObject(he::RenderObject *object);
	void Update(double dt);
	void Render();
	//Getter-Setters
	GLKVector2 GetPosition();
	void SetPosition(GLKVector2 position);
	
private:
	GLKVector2 dir_;		//direction
	GLKVector2 pos_;		//position
	GLKVector2 speed_;	//speed
	he::RenderObject *sprite_;	//sprite
};

#endif /* defined(__HEAssets__RunningObject__) */
