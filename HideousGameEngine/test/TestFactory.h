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
//Test cases factories
RectColorTest *MakeRectColorTest(float w, float h){
	return new RectColorTest(w, h);
}

#include "RectTextureTest/RectTextureTest.h"
RectTextureTest *MakeRectTextureTest(float w, float h){
	return new RectTextureTest(w, h);
}

#include "RectTextTest/RectTextTest.h"
RectTextTest *MakeRectTextTest(float w, float h){
	return new RectTextTest(w, h);
}

#include "MultiShadersTest/MultiShadersTest.h"
MultiShadersTest *MakeMultiShadersTest(float w, float h){
	return new MultiShadersTest(w, h);
}

#include "MultiFontTest/MultiFontTest.h"
MultiFontTest *MakeMultiFontTest(float w, float h){
	return new MultiFontTest(w,h);
}

#include "AnimationTest/AnimationTest.h"
AnimationTest *MakeAnimationTest(float w, float h){
	return new AnimationTest(w, h);
}

#include "TextureBigBangTest/TextureBigBangTest.h"
TextureBigBangTest *MakeTextureBigBangTest(float w, float h){
	return new TextureBigBangTest(w,h);
}

#include "GestureTest/GestureTest.h"
GestureTest *MakeGestureTest(float w, float h){
	return new GestureTest(w,h);
}

#include "UITest/UITest.h"
UITest *MakeUITest(float w, float h){
	return new UITest(w,h);
}

#include "ParticleTest/ParticleTest.h"
ParticleTest *MakeParticlesTest(float w, float h){
	return new ParticleTest(w,h);
}

#include "SpineTest/SpineTest.h"
SpineTest *MakeSpineTest(float w, float h){
	return new SpineTest(w, h);
}
#endif
