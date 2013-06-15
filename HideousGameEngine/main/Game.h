//
//  Game.h
//  HideousGameEngine
//
//  Created by Sid on 15/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__Game__
#define __HideousGameEngine__Game__
#include <he/Main/HideousGame.h>

class GameAllocator : public he::GameAllocator{
public:
	explicit GameAllocator(GLKVector3 clear_color);
	
private:
	he::Game* allocate(const GLKVector3 &clear_color);
};

#endif /* defined(__HideousGameEngine__Game__) */
