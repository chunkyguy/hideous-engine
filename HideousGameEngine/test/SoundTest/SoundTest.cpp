//
//  SoundTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 22/09/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "SoundTest.h"
#include <string>
#include <he/SoundEngine/SoundPlayer.h>
#include <he/Utils/ResourcePath.hpp>

void SoundTest::init() {
 gesture_listener_.reset((he::CreateGestureListener(this, &SoundTest::HandleGesture)));
 std::string file(he::ResourcePath() + "background.m4a");
 he::SoundPlayer_PlayMusic(he::g_SoundPlayer, file.c_str());
}

SoundTest::~SoundTest() {
}

void SoundTest::update(float dt){
}

void SoundTest::render(){
}

void SoundTest::HandleGesture(const he::Gesture &gesture) {
 const char * sounds[] = { "sound.caf", "splash.aiff"};
 
 if (gesture.state_ == he::Gesture::kEnd && gesture.action_ == he::Gesture::kTap) {
  
  std::string file(he::ResourcePath() + sounds[rand()%(sizeof(sounds)/sizeof(sounds[0]))]);
  he::SoundPlayer_PlayEffect(he::g_SoundPlayer, file.c_str());
 }
}
