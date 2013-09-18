//
//  CollisionTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 17/09/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "CollisionTest.h"

#include <he/UI/View.h>
#include <he/Utils/Transform.h>
#include <he/Utils/Screen.h>
#include <he/Utils/GLKMath_Additions.h>
#include <he/Shaders/ColorShader.h>
#include <he/UI/GradientView.h>
#include <he/Utils/Utils.h>
#include <he/Utils/DebugHelper.h>
#include <he/Utils/Frame.h>

/*************************************************************************************************************************************
 *	MARK: CollisionView
 *************************************************************************************************************************************/
class CollisionView : public he::GradientView {
public:
	CollisionView(const he::Transform &transform, he::Gradient *gradient, float speed);
	virtual void Update(float dt);
	virtual void Render();
	virtual GLKVector2 GetSize() const;
	
private:
	float speed_;
};

CollisionView::CollisionView(const he::Transform &transform, he::Gradient *gradient, float speed) :
he::GradientView(transform, gradient),
speed_(speed)
{}

void CollisionView::Update(float dt) {
	transform_.position.x += dt * speed_;
	if (transform_.position.x > he::g_Screen->GetSize().x/2.0f) {
		transform_.position.x = -he::g_Screen->GetSize().x/2.0f;
	}
	transform_.rotation.w += dt * speed_;
	he::GradientView::Update(dt);
}

void CollisionView::Render() {
	he::GradientView::Render();
}

GLKVector2 CollisionView::GetSize() const {
	return he::GradientView::GetSize();
}

/*************************************************************************************************************************************
 *	MARK: CollisionTest
 *************************************************************************************************************************************/
//static const float kSleep = 0.01f;

void CollisionTest::init() {
	//	sleep_ = kSleep;
	float size_x = 100.0f;
	float size_y = 50.0f;
	shader_.reset(new he::ColorShader);
	gradient_.reset(he::gradient::Create(GLKVector2Make(size_x, size_y), shader_.get(),
										 GLKVector4Make(1.0f, 0.0f, 0.0f, 0.5f),
										 GLKVector4Make(0.0f, 1.0f, 0.0f, 0.5f),
										 GLKVector4Make(0.0f, 0.0f, 1.0f, 0.5f),
										 GLKVector4Make(1.0f, 1.0f, 1.0f, 0.5f)
										 ));
	view_.reset(new he::View(he::Transform_Create(GLKVector3Make(0.0f, 0.0f, he::g_Screen->z_))));
	
	subviews_[0] = static_cast<CollisionView*>(view_->MoveSubview(new CollisionView(he::Transform_Create(GLKVector3Make(0.0f, 0.0f, 0.0f), GLKVector4Make(0.0f, 0.0f, 1.0f, 0.0f)), gradient_.get(), 0.0f)));
	subviews_[1] = static_cast<CollisionView*>(view_->MoveSubview(new CollisionView(he::Transform_Create(GLKVector3Make(80, 50, 0.0f), GLKVector4Make(0.0f, 0.0f, 1.0f, GLKMathDegreesToRadians(150.0f))), gradient_.get(),he::Randf()+1.0f)));
	
	print_state();
}

void CollisionTest::print_state() {
	bool hit_test = HitTest(subviews_[0], subviews_[1]);
	he_Trace("hit_test: %@\n",hit_test);
}

void CollisionTest::update(float dt) {
//	sleep_ -= dt;
//	if (sleep_ > 0.0f){
//		return;
//	}
	view_->Update(dt);
	print_state();
//	sleep_ = kSleep;
}

void CollisionTest::render() {
	view_->Render();
}

// EOF
