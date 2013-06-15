//
//  FlashTest.h
//  HideousGameEngine
//
//  Created by Sid on 06/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__FlashTest__
#define __HideousGameEngine__FlashTest__

#include <he/Main/HideousGame.h>

#include <he/EventLoop/Gesture.h>

class FlashMovie;
class FlashMovieAssets;

class FlashTest : public he::Game {
public:
	FlashTest(GLKVector3 clear_color = GLKVector3Make(0.5f, 0.5f, 0.5f));
	~FlashTest();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	void update(float dt);
	void render();
	
	FlashMovie *movie_;
	FlashMovieAssets *assets_;
	he::GestureListener<FlashTest> *gesture_listener_;
};

#endif /* defined(__HideousGameEngine__FlashTest__) */
