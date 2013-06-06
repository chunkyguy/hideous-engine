//
//  TestFactory.h
//  HideousGameEngine
//
//  Created by Sid on 10/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_TestFactory_h
#define HideousGameEngine_TestFactory_h

#include "RectColorTest/RectColorTest.h"
#include "RectTextureTest/RectTextureTest.h"
#include "RectTextTest/RectTextTest.h"
#include "MultiShadersTest/MultiShadersTest.h"
#include "MultiFontTest/MultiFontTest.h"
#include "AnimationTest/AnimationTest.h"
#include "TextureBigBangTest/TextureBigBangTest.h"
#include "GestureTest/GestureTest.h"
#include "UITest/UITest.h"
#include "ParticleTest/ParticleTest.h"
#include "SpineTest/SpineTest.h"
#include "FlashTest/FlashTest.h"

template <typename T>
T* MakeTest(float w, float h){
	return new T(w, h);
}
#endif
