//
//  RunningSquare.h
//  HideousGameEngine
//
//  Created by Sid on 10/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

//	A sample case on how can you impl your own things over basic RenderObjects.
//	Here we use RectColor as base and add other properties to it.

#ifndef __HideousGameEngine__RunningSquare__
#define __HideousGameEngine__RunningSquare__

#include <he/Utils/GLKMath_Additions.h>
#include <he/Utils/Transform.h>

namespace he{
	class ColorShader;
	class RenderObject;
	class ColorVertex;
}

class RunningSquare{
public:
	typedef enum {kLiving, kZombie, kDead} Life;

	~RunningSquare();
	RunningSquare(he::ColorShader *shader);
	void Update(float dt);
	void Render();
	//Getter-Setters
	Life GetLifeState();
	void SetDead();
	
private:
	GLKVector4 color_;
	GLKVector2 direction_;			//direction
	Life life_state_;
	GLKVector2 speed_;				//speed
	he::RenderObject *sprite_;		//sprite
	he::Transform transform_;		//transform
	he::ColorVertex *vertex_data_;
};
#endif /* defined(__HideousGameEngine__RunningSquare__) */
