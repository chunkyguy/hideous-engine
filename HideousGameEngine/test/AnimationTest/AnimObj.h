//
//  AnimObj.h
//  HideousGameEngine
//
//  Created by Sid on 01/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__AnimObj__
#define __HideousGameEngine__AnimObj__

#include <GLKit/GLKMath.h>

#include <he/Utils/Transform.h>

namespace he{
	class RenderObject;
	class RectColorSh;
	class VertexCol;
	class AnimationChain;
}

class AnimObj{
public:
	~AnimObj();
	AnimObj();
	void Update(double dt);
	void Render();
	void TouchEnd(GLKVector2 pt);

private:
	he::RenderObject *render_object_;
	he::VertexCol *vert_data_;
	he::RectColorSh *shader_;
	he::Transform transform_;
	he::Transform *tmp_transform_;	//While animating hold transform vars.
	he::AnimationChain *anim_chain_;
};
#endif /* defined(__HideousGameEngine__AnimObj__) */
