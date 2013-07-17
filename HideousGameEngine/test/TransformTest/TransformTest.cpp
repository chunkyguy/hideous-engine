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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	MARK: TransformTest
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TransformTest::init() {
	shader_.reset(new he::ColorShader);
	gradient_.reset(he::gradient::Create(GLKVector2Make(20.0f, 25.0f), shader_.get(), GLKVector4Make(0.45f, 0.23f, 0.65f, 1.0f), GLKVector4Make(0.45f, 0.78f, 0.12f, 1.0f)));

	//universe
	universe_.reset(new Universe(he::Transform_Create(GLKVector2Make(0.0f, 0.0f))));

	//sun
	HeavenlyBody *sun = new HeavenlyBody(he::Transform_Create(GLKVector3Make(100.0f, 0.0f, 0.0f)), gradient_.get(), 0.33f);
	universe_->MoveSubview(sun);
	
	//earth
	HeavenlyBody *earth = new HeavenlyBody(he::Transform_Create(GLKVector3Make(100.0f, 0.0f, 0.0f)), gradient_.get(), 0.66f);
	sun->MoveSubview(earth);

	//moon
	HeavenlyBody *moon = new HeavenlyBody(he::Transform_Create(GLKVector3Make(50.0f, 0.0f, 0.0f)), gradient_.get(), 0.99f);
	earth->MoveSubview(moon);
}

void TransformTest::update(float dt) {
	universe_->Update(dt);
}

void TransformTest::render() {
	universe_->Render();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	MARK: Universe
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Universe::Universe(const he::Transform &transform) :
View(transform)
{}

void Universe::Update(float dt) {
	View::Update(dt);
	transform_.rotation.w += dt*0.05f;
}

void Universe::Render() {
	View::Render();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	MARK: HeavenlyBodies
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeavenlyBody::HeavenlyBody(const he::Transform &transform, he::Gradient *grad, float speed) :
he::GradientView(transform, grad),
speed_(speed)
{}

void HeavenlyBody::Update(float dt) {
	GradientView::Update(dt);
	transform_.rotation.w += dt*speed_;
}

void HeavenlyBody::Render() {
	GradientView::Render();
}

// EOF //
