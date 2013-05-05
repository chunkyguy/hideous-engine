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
RectColorTest *MakeRectColorTest(double w, double h){
	return new RectColorTest(w, h);
}

#include "RectTextureTest/RectTextureTest.h"
RectTextureTest *MakeRectTextureTest(double w, double h){
	return new RectTextureTest(w, h);
}

#include "RectTextTest/RectTextTest.h"
RectTextTest *MakeRectTextTest(double w, double h){
	return new RectTextTest(w, h);
}

#include "MultiShadersTest/MultiShadersTest.h"
MultiShadersTest *MakeMultiShadersTest(double w, double h){
	return new MultiShadersTest(w, h);
}

#include "MultiFontTest/MultiFontTest.h"
MultiFontTest *MakeMultiFontTest(double w, double h){
	return new MultiFontTest(w,h);
}

#include "AnimationTest/AnimationTest.h"
AnimationTest *MakeAnimationTest(double w, double h){
	return new AnimationTest(w, h);
}

#include "TextureBigBangTest/TextureBigBangTest.h"
TextureBigBangTest *MakeTextureBigBangTest(double w, double h){
	return new TextureBigBangTest(w,h);
}

#include "GestureTest/GestureTest.h"
GestureTest *MakeGestureTest(double w, double h){
	return new GestureTest(w,h);
}

#include "UITest/UITest.h"
UITest *MakeUITest(double w, double h){
	return new UITest(w,h);
}

#include "ParticleTest/ParticleTest.h"
ParticleTest *MakeParticlesTest(double w, double h){
	return new ParticleTest(w,h);
}

#endif
