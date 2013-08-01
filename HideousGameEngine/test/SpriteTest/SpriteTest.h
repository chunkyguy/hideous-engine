//
//  SpriteTest.h
//  HideousGameEngine
//
//  Created by Sid on 25/07/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__SpriteTest__
#define __HideousGameEngine__SpriteTest__
#include <memory>

#include <he/Main/HideousGame.h>
#include <he/Shaders/TextureShader.h>
#include <he/Texture/TextureAtlas.h>
#include <he/UI/Sprite.h>
#include <he/EventLoop/Gesture.h>

class SpriteTest : public he::Game {
public:
	~SpriteTest();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	virtual void init();
	virtual void update(float dt);
	virtual void render();
	
	void animation_begin(const GLKVector2 &pos);
	void animation_end();
	
	std::unique_ptr<he::TextureAtlas> atlas_;
	std::unique_ptr<he::TextureShader> texture_shader_;
	he::View *view_;
	std::unique_ptr<he::Sprite> sprite_;
	he::SpriteView *sprite_view_;
	std::unique_ptr<he::GestureListener<SpriteTest>, he::GestureListenerDeleter<SpriteTest>> gesture_listener_;
	bool animating_;
};

#endif /* defined(__HideousGameEngine__SpriteTest__) */
