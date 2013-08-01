//
//  SpriteTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 25/07/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "SpriteTest.h"

#include <he/Utils/Transform.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Screen.h>

void SpriteTest::init() {
	gesture_listener_.reset((he::CreateGestureListener(this, &SpriteTest::HandleGesture)));
	
	// Create shader
	texture_shader_.reset(new he::TextureShader);
	std::string fish_atlas_data_path(he::ResourcePath() + "fishmotion.xml");
	std::string fish_atlas_img_path(he::ResourcePath() + "fishmotion.png");
	atlas_.reset(new he::TextureAtlas(fish_atlas_data_path, fish_atlas_img_path, he::TextureAtlas::kStarling));

	view_ = new he::View(he::Transform_Create(GLKVector3Make(0.0f, 0.0f, he::g_Screen->z_)));

	animating_ = false;
}

SpriteTest::~SpriteTest() {
	delete view_;
}

void SpriteTest::update(float dt){
	view_->Update(dt);
}

void SpriteTest::render(){
	view_->Render();
}

void SpriteTest::HandleGesture(const he::Gesture &gesture) {
	if (gesture.state_ == he::Gesture::kEnd && gesture.action_ == he::Gesture::kTap) {
		if (animating_) {
			animation_end();
		} else {
			animation_begin(gesture.GetHitPoint());
		}
	}
}

void SpriteTest::animation_begin(const GLKVector2 &pos) {
	std::string fish_sprite_name("fishmoving");
	sprite_.reset(he::sprite::Create(texture_shader_.get(), atlas_.get(), fish_sprite_name, -1, 0, 30.0f));

	GLKVector3 position = GLKVector3Make(100.0f, -100.0f, 0.0f);
	float angle = atan2f(pos.y - position.y, pos.x - position.x);
	he::Transform fish_trans = he::Transform_Create(position, GLKVector4Make(0.0f, 0.0f, 1.0f, angle));
	sprite_view_ = new he::SpriteView(fish_trans, sprite_.get());
	view_->MoveSubview(sprite_view_);
	animating_ = true;
}

void SpriteTest::animation_end() {
	view_->RemoveSubview(sprite_view_);
	animating_ = false;
}
// EOF //
