//
//  TexturedSprite.h
//  HideousGameEngine
//
//  Created by Sid on 04/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__TexturedSprite__
#define __HideousGameEngine__TexturedSprite__
#include <GLKit/GLKMath.h>

namespace he{
	class RenderObject;
}

class TexturedSprite{
public:
	typedef enum{kLiving, kZombie, kDead}Life;
	
	~TexturedSprite();
	TexturedSprite();
	bool Init(int iD, he::RenderObject *sp, GLKVector2 at);
	void Update(double dt);
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
	he::RenderObject *sprite_;		//sprite
	int ID_;
};
#endif /* defined(__HideousGameEngine__TexturedSprite__) */
