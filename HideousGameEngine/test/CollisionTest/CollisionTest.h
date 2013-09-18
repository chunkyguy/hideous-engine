//
//  CollisionTest.h
//  HideousGameEngine
//
//  Created by Sid on 17/09/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__CollisionTest__
#define __HideousGameEngine__CollisionTest__

#include <memory>

#include <he/Main/HideousGame.h>

namespace he {
	class View;
	class ColorShader;
	class Gradient;
}
class CollisionView;

class CollisionTest : public he::Game {
private:
	virtual void init();
	virtual void update(float dt);
	virtual void render();
	void print_state();
	
	std::unique_ptr<he::ColorShader> shader_;
	std::unique_ptr<he::Gradient> gradient_;
	std::unique_ptr<he::View> view_;
	CollisionView *subviews_[2];
	float sleep_;
};
#endif /* defined(__HideousGameEngine__CollisionTest__) */
