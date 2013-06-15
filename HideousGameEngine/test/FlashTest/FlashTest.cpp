//
//  FlashTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 06/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "FlashTest.h"

#include <OpenGLES/ES2/gl.h>

#include <he/Animation/AnimationLoop.h>
#include <he/Shaders/TextureShader.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Utils.h>

#include "FlashMovie.h"

FlashTest::FlashTest(GLKVector3 clear_color) :
he::Game(clear_color){
	// load
	std::string data_path(he::ResourcePath() + "fishmotion.xml");
	std::string img_path(he::ResourcePath() + "fishmotion.png");
	assets_ = new FlashMovieAssets(new he::TextureAtlas(data_path, img_path, he::TextureAtlas::kStarling), new he::TextureShader);
	
	std::string name("fishmoving");
	movie_ = new FlashMovie(name, assets_, GLKVector2Make(0, 0), 0, 24.0f);
	
	gesture_listener_ = new he::GestureListener<FlashTest>(this, &FlashTest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listener_);
}

FlashTest::~FlashTest(){
	delete movie_;
	delete assets_;
	he::g_EventLoop->RemoveListener(gesture_listener_);
	delete gesture_listener_;
}

void FlashTest::update(float dt){
	movie_->Update(dt);
}

void FlashTest::render(){
	movie_->Render();
}

void FlashTest::HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ == he::Gesture::kTap && gesture.state_ == he::Gesture::kEnd){
		movie_->TouchPoint(gesture.GetHitPoint());
	}
}
///EOF
