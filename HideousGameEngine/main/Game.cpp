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
//#define TEST_RECT_TEXT
//#define TEST_MULTI_SHADERS
//#define TEST_MULTI_FONT
//#define TEST_ANIMATION
//#define TEST_TEXTURE_BIG_BANG
//#define TEST_GESTURE
//#define TEST_PARTICLES
#define TEST_UI
//#define TEST_SPINE
//#define TEST_FLASH

template <typename T>
T* CreateGameInstance(GLKVector3 clear_color){
	return new T(clear_color);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: GameAllocator
//////////////////////////////////////////////////////////////////////////////////////////////////////
GameAllocator::GameAllocator(GLKVector3 clear_color) :
he::GameAllocator(clear_color)
{}

he::Game* GameAllocator::allocate(const GLKVector3 &clear_color){
	
#if defined(TEST_RECT_COLOR)
	return CreateGameInstance<RectColorTest>(clear_color);
#elif defined(TEST_RECT_TEXTURE)
	return CreateGameInstance<RectTextureTest>(clear_color);
#elif defined(TEST_RECT_TEXT)
	return CreateGameInstance<RectTextTest>(clear_color);
#elif defined(TEST_MULTI_SHADERS)
	return CreateGameInstance<MultiShadersTest>(clear_color);
#elif defined(TEST_MULTI_FONT)
	return MakeTest<MultiFontTest>(clear_color);
#elif defined(TEST_ANIMATION)
	return CreateGameInstance<AnimationTest>(clear_color);
#elif defined(TEST_TEXTURE_BIG_BANG)
	return CreateGameInstance<TextureBigBangTest>(clear_color);
#elif defined(TEST_GESTURE)
	return CreateGameInstance<GestureTest>(clear_color);
#elif defined(TEST_UI)
	return CreateGameInstance<UITest>(clear_color);
#elif defined(TEST_PARTICLES)
	return CreateGameInstance<ParticleTest>(clear_color);
#elif defined(TEST_SPINE)
	return CreateGameInstance<SpineTest>(clear_color);
#elif defined(TEST_FLASH)
	return CreateGameInstance<FlashTest>(clear_color);
#endif
	
}

///EOF
