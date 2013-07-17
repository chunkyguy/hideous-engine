//
//  TransformTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 14/07/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "TransformTest.h"

#include <he/Utils/Transform.h>
#include <he/Utils/Frame.h>
#include <he/Utils/GLKMath_Additions.h>

void TransformTest::init() {
	shader_.reset(new he::ColorShader);
	universe_.reset(new Universe(he::Frame(he::Transform_Create(GLKVector2Make(0.0f, 0.0f)))));

	gradient_.reset(he::gradient::Create(GLKVector2Make(10.0f, 10.0f), shader_.get(), GLKVector4Make(1.0f, 0.0f, 0.0f, 1.0f)));
	he::Frame frame(he::Transform_Create(GLKVector3Make(0.0f, 0.0f, 0.0f)), GLKVector2Make(40.0f, 40.0f));
	HeavenlyBody *sun = new HeavenlyBody(frame, gradient_.get());
	universe_->MoveSubview(sun);
}

void TransformTest::update(float dt) {
	universe_->Update(dt);
}

void TransformTest::render() {
	universe_->Render();
}
// EOF //
