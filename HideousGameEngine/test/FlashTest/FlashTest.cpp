//
//  FlashTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 06/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "FlashTest.h"

#include <he/Utils/Utils.h>

FlashTest::FlashTest(float w, float h){
	he::GlobalsInit(w, h);
}

FlashTest::~FlashTest(){
	he::GlobalsDestroy();
}

void FlashTest::Update(float dt){
	
}

void FlashTest::Render(){
	
}