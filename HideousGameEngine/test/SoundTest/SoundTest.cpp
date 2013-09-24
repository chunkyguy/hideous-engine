//
//  SoundTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 22/09/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "SoundTest.h"

#include <he/SoundEngine/SoundPlayer.h>

void SoundTest::init() {
	gesture_listener_.reset((he::CreateGestureListener(this, &SoundTest::HandleGesture)));
	he::SoundPlayer_PlayMusic(he::g_SoundPlayer, "background", "m4a");
}

SoundTest::~SoundTest() {
}

void SoundTest::update(float dt){
}

void SoundTest::render(){
}

void SoundTest::HandleGesture(const he::Gesture &gesture) {
	struct Snd {
		const char *name[2];
	} sounds[] = {
		{"sound", "caf"},
		{"splash", "aiff"}
	};
	
	if (gesture.state_ == he::Gesture::kEnd && gesture.action_ == he::Gesture::kTap) {
	
		Snd s = sounds[rand()%(sizeof(sounds)/sizeof(sounds[0]))];
		he::SoundPlayer_PlayEffect(he::g_SoundPlayer, s.name[0], s.name[1]);
//		GLKVector2 pt = gesture.GetHitPoint();
//		GLKVector3 pos = GLKVector3Make(pt.x, pt.y, 0.0f);
	}
}
