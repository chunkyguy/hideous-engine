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

#include <GLKit/GLKMath.h>

namespace he{
	class RectColorSh;
	class RenderObject;
	class VertexCol;
}

class RunningSquare{
public:
	typedef enum {kLiving, kZombie, kDead} Life;

	~RunningSquare();
	RunningSquare(he::RectColorSh *shader);
	void Update(double dt);
	void Render();
	//Getter-Setters
	GLKVector2 GetPosition();
	void SetPosition(GLKVector2 position);
	Life GetLifeState();
	void SetDead();
	
private:
	Life life_state_;
	GLKVector2 speed_;	//speed
	GLKVector2 direction_;		//direction
	GLKVector2 position_;		//position
	he::RenderObject *sprite_;	//sprite
	GLKMatrix4 mvp_;
	GLKVector4 color_;
	he::VertexCol *vertex_data_;
};
#endif /* defined(__HideousGameEngine__RunningSquare__) */
