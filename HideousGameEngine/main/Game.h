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

class GameConfig : public he::GameConfig{	
public:
	explicit GameConfig(GLKVector3 config);
private:
	virtual he::Game* alloc_game();
};

#endif /* defined(__HideousGameEngine__Game__) */
