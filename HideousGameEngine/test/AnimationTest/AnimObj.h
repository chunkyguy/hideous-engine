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
	class ColorShader;
	class ColorVertex;
}

class AnimObj{
public:
	~AnimObj();
	AnimObj(int ID, he::ColorShader *shader);
	void Update(float dt);
	void Render();
	void TouchEnd(GLKVector2 pt);
	void AnimationCallback(he::Animation::ID animation_id);
	
private:
	void end_animations();
	
	int id_;
	he::RenderObject *render_object_;
	he::ColorVertex *vert_data_;
	he::ColorShader *shader_;
	he::Transform transform_;
	he::AnimationListener<AnimObj> *animation_listener_;
	he::Animation::ID scale_anim_descent_id_;
	he::Animation::ID trans_anim_descent_id_;
	//he::Transform *tmp_transform_;	//While animating hold transform vars.
									//he::AnimationChain *anim_chain_;
};
#endif /* defined(__HideousGameEngine__AnimObj__) */
