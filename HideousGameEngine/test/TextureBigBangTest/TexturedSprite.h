//
//  TexturedSprite.h
//  HideousGameEngine
//
//  Created by Sid on 04/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__TexturedSprite__
#define __HideousGameEngine__TexturedSprite__
#include <he/Utils/GLKMath_Additions.h>
#include <he/Utils/Transform.h>

namespace he{
	class RenderObject;
}

class TexturedSprite{
public:
	typedef enum{kLiving, kZombie, kDead}Life;
	
	~TexturedSprite();
	TexturedSprite();
	bool Init(int iD, he::RenderObject *sp, he::Transform transform);
	void Update();
	//Getter-Setters
//	he::Transform GetTransform();
//	void SetTransform(GLKVector2 transform);

	Life GetLifeState();
	void SetDead();
	
private:
	Life life_state_;
	GLKVector2 speed_;	//speed
	GLKVector2 direction_;		//direction
	he::Transform transform_;		//transform
	he::RenderObject *sprite_;		//sprite
	int ID_;
};
#endif /* defined(__HideousGameEngine__TexturedSprite__) */
