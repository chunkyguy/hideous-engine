//
//  Game.cpp
//  HideousGameEngine
//
//  Created by Sid on 15/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "Game.h"

#include "../test/RectColorTest/RectColorTest.h"
#include "../test/RectTextureTest/RectTextureTest.h"
#include "../test/RectTextTest/RectTextTest.h"
#include "../test/MultiShadersTest/MultiShadersTest.h"
#include "../test/MultiFontTest/MultiFontTest.h"
#include "../test/AnimationTest/AnimationTest.h"
#include "../test/TextureBigBangTest/TextureBigBangTest.h"
#include "../test/GestureTest/GestureTest.h"
#include "../test/UITest/UITest.h"
#include "../test/ParticleTest/ParticleTest.h"
#include "../test/SpineTest/SpineTest.h"
#include "../test/FlashTest/FlashTest.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: Helper
//////////////////////////////////////////////////////////////////////////////////////////////////////
//Enable only one of these
//#define TEST_RECT_COLOR
//#define TEST_RECT_TEXTURE
#define TEST_RECT_TEXT
//#define TEST_MULTI_SHADERS
//#define TEST_MULTI_FONT
//#define TEST_ANIMATION
//#define TEST_TEXTURE_BIG_BANG
//#define TEST_GESTURE
//#define TEST_PARTICLES
//#define TEST_UI
//#define TEST_SPINE
//#define TEST_FLASH

template <typename T>
T* AllocGameInstance(){
	return new T();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: GameAllocator
//////////////////////////////////////////////////////////////////////////////////////////////////////
GameConfig::GameConfig(GLKVector3 config) :
he::GameConfig(config)
{}

he::Game* GameConfig::alloc_game(){
	
#if defined(TEST_RECT_COLOR)
	return AllocGameInstance<RectColorTest>();
#elif defined(TEST_RECT_TEXTURE)
	return AllocGameInstance<RectTextureTest>();
#elif defined(TEST_RECT_TEXT)
	return AllocGameInstance<RectTextTest>();
#elif defined(TEST_MULTI_SHADERS)
	return AllocGameInstance<MultiShadersTest>();
#elif defined(TEST_MULTI_FONT)
	return AllocGameInstance<MultiFontTest>();
#elif defined(TEST_ANIMATION)
	return AllocGameInstance<AnimationTest>();
#elif defined(TEST_TEXTURE_BIG_BANG)
	return AllocGameInstance<TextureBigBangTest>();
#elif defined(TEST_GESTURE)
	return AllocGameInstance<GestureTest>();
#elif defined(TEST_UI)
	return AllocGameInstance<UITest>();
#elif defined(TEST_PARTICLES)
	return AllocGameInstance<ParticleTest>();
#elif defined(TEST_SPINE)
	return AllocGameInstance<SpineTest>();
#elif defined(TEST_FLASH)
	return AllocGameInstance<FlashTest>();
#endif
	
}

///EOF
