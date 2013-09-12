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
#include <he/Animation/SpriteAnimation.h>

#pragma mark - SpriteTest -
const float kNewAnimDelay = 0.5f;

void SpriteTest::init() {
	gesture_listener_.reset((he::CreateGestureListener(this, &SpriteTest::HandleGesture)));
	
	// Create shader
	texture_shader_.reset(new he::TextureShader);
	std::string fish_atlas_data_path(he::ResourcePath() + "playscreen_ss.xml");
	std::string fish_atlas_img_path(he::ResourcePath() + "playscreen_ss.png");
	atlas_.reset(new he::TextureAtlas(fish_atlas_data_path, fish_atlas_img_path, he::TextureAtlas::kStarling));

	view_ = new he::View(he::Transform_Create(GLKVector3Make(0.0f, 0.0f, he::g_Screen->z_)));

	animating_ = false;
	
	new_anim_delay_ = kNewAnimDelay;

	sprite_data_.reset(he::sprite::Create(atlas_.get(), "mc_deadfish"));
}

SpriteTest::~SpriteTest() {
	delete view_;
}

void SpriteTest::update(float dt){
	new_anim_delay_ -= dt;
	if (new_anim_delay_ < 0.0f) {
		GLKVector3 position = GLKVector3Make(he::Randf()*he::g_Screen->width_ - he::g_Screen->width_/2.0, he::Randf()*he::g_Screen->height_ - he::g_Screen->height_/2.0, 0.0f);
		start_animation(position);
		new_anim_delay_ = kNewAnimDelay * he::Randf();
	}
	view_->Update(dt);
}

void SpriteTest::render(){
	view_->Render();
}

void SpriteTest::HandleGesture(const he::Gesture &gesture) {
	if (gesture.state_ == he::Gesture::kEnd && gesture.action_ == he::Gesture::kTap) {
		GLKVector2 pt = gesture.GetHitPoint();
		GLKVector3 pos = GLKVector3Make(pt.x, pt.y, 0.0f);
		start_animation(pos);
	}
}

void SpriteTest::start_animation(const GLKVector3 & position) {
	float angle = atan2f(position.y, position.x);
	he::Transform trans = he::Transform_Create(position, GLKVector4Make(0.0f, 0.0f, 1.0f, angle));
	printf("Start\n");
	view_->MoveSubview(new SpriteTestView(trans,
										  sprite_data_.get(),
										  texture_shader_.get(),
										  atlas_.get(),
										  [=](SpriteTestView* vw){
		printf("End\n");
		view_->RemoveSubview(vw);
	}));
}


//void SpriteTest::animation_begin(const GLKVector2 &pos) {
//	std::string fish_sprite_name("mc_deadfish");
//	sprite_.reset(he::sprite::Create(texture_shader_.get(), atlas_.get(), fish_sprite_name, 1, nullptr, 14, 12.0f));
//	sprite_->StartAnimation();
//	
//	for (int i = 0; i < NUM_SPRITES; ++i) {
//		GLKVector3 position = GLKVector3Make(he::Randf()*he::g_Screen->width_ - he::g_Screen->width_/2.0, he::Randf()*he::g_Screen->height_ - he::g_Screen->height_/2.0, 0.0f);
//		float angle = atan2f(pos.y - position.y, pos.x - position.x);
//		he::Transform fish_trans = he::Transform_Create(position, GLKVector4Make(0.0f, 0.0f, 1.0f, angle));
//		sprite_view_[i] = static_cast<he::SpriteView*>(view_->MoveSubview(new he::SpriteView(fish_trans, sprite_.get())));
//	}
//	animating_ = true;
//}

#pragma mark - SpriteTestView -
SpriteTestView::SpriteTestView(const he::Transform &transform,
							   he::SpriteAnimationData *sprite_data,
							   he::TextureShader *texture_shader,
							   he::TextureAtlas *atlas,
							   std::function<void(SpriteTestView*)> callback) :
he::View(transform),
callback_(callback),
anim_listener_(new he::AnimationListener<SpriteTestView>(this, &SpriteTestView::DoneAnimation)),
sprite_(he::sprite::Create(sprite_data, texture_shader, atlas, 1, anim_listener_.get(), 14, 12.0f))
{
	sprite_->StartAnimation();
	this->MoveSubview(new he::SpriteView(he::Transform_Create(GLKVector3Make(0.0, 0.0, 0.0)), sprite_.get()));
}

SpriteTestView::~SpriteTestView() {
}

void SpriteTestView::Update(float dt) {
	he::View::Update(dt);
}

void SpriteTestView::Render() {
	he::View::Render();
}

void SpriteTestView::DoneAnimation(he::Animation::ID aid) {
	callback_(this);
}

// EOF //
