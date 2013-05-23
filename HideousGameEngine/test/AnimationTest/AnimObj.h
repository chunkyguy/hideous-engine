//
//  AnimObj.h
//  HideousGameEngine
//
//  Created by Sid on 01/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__AnimObj__
#define __HideousGameEngine__AnimObj__

#include <he/Utils/GLKMath_Additions.h>

#include <he/Animation/Animation.h>
#include <he/Utils/Transform.h>

namespace he{
	class RenderObject;
	class RectColorSh;
	class VertexCol;
}

class AnimObj{
public:
	~AnimObj();
	AnimObj(he::RectColorSh *shader);
	void Update(double dt);
	void Render();
	void TouchEnd(GLKVector2 pt);
	void AnimationCallback(int animation_id);
	
private:

	
	he::RenderObject *render_object_;
	he::VertexCol *vert_data_;
	he::RectColorSh *shader_;
	he::Transform transform_;
	he::Animation<GLKVector2> *scale_animation_;
	he::Animation<GLKVector2> *trans_animation_;
	he::AnimationListener<AnimObj> *animation_listener_;
	//he::Transform *tmp_transform_;	//While animating hold transform vars.
									//he::AnimationChain *anim_chain_;
};
#endif /* defined(__HideousGameEngine__AnimObj__) */
