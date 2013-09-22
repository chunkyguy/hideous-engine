//
//  SoundTest.h
//  HideousGameEngine
//
//  Created by Sid on 22/09/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__SoundTest__
#define __HideousGameEngine__SoundTest__

#include <memory>

#include <he/Main/HideousGame.h>
#include <he/EventLoop/Gesture.h>

class SoundTest : public he::Game {
public:
	~SoundTest();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	virtual void init();
	virtual void update(float dt);
	virtual void render();

	std::unique_ptr<he::GestureListener<SoundTest>, he::GestureListenerDeleter<SoundTest>> gesture_listener_;
};

#endif /* defined(__HideousGameEngine__SoundTest__) */
