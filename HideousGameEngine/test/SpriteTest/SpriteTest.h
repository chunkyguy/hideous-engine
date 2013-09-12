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
#include <he/Animation/SpriteAnimation.h>

class SpriteTestView : public he::View {
public:
	SpriteTestView(const he::Transform &transform,
				   he::SpriteAnimationData *sprite_data,
				   he::TextureShader *texture_shader,
				   he::TextureAtlas *atlas,
				   std::function<void(SpriteTestView*)> callback);
	
	virtual ~SpriteTestView();
	virtual void Update(float dt);
	virtual void Render();
	void DoneAnimation(he::Animation::ID aid);
	
private:
	std::unique_ptr<he::AnimationListener<SpriteTestView>> anim_listener_;
	std::function<void(SpriteTestView*)> callback_;
	std::unique_ptr<he::Sprite>	sprite_;
};

class SpriteTest : public he::Game {
public:
	~SpriteTest();
	void HandleGesture(const he::Gesture &gesture);
	
private:
	virtual void init();
	virtual void update(float dt);
	virtual void render();
	void start_animation(const GLKVector3 & position);
	
	std::unique_ptr<he::GestureListener<SpriteTest>, he::GestureListenerDeleter<SpriteTest>> gesture_listener_;
	std::unique_ptr<he::TextureAtlas> atlas_;
	std::unique_ptr<he::TextureShader> texture_shader_;
	he::View *view_;
	std::unique_ptr<he::SpriteAnimationData> sprite_data_;
	bool animating_;
	float new_anim_delay_;
};

#endif /* defined(__HideousGameEngine__SpriteTest__) */
