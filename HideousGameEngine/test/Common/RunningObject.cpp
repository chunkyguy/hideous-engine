//
//  RunningObject.cpp
//  HEAssets
//
//  Created by Sid on 28/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "RunningObject.h"

#include <he/RenderObject/RenderObject.h>
#include <he/Utils/Screen.h>
#include <he/Utils/Utils.h>

RunningObject::RunningObject(he::RenderObject *object) :
speed_(GLKVector2Make(0.1 + he::Randf()*5.0, 0.1 + he::Randf()*5.0)),
dir_(GLKVector2Make(rand()%2?-1:1, rand()%2?-1:1)),
pos_(GLKVector2Make(-he::g_Screen->width_/2+he::Randf()*he::g_Screen->width_, -he::g_Screen->height_/2+he::Randf()*he::g_Screen->height_)),
sprite_(object)
{}

GLKVector2 RunningObject::GetPosition(){
	return pos_;
}

void RunningObject::SetPosition(GLKVector2 position){
	pos_ = position;
	GLKMatrix4 tMat = GLKMatrix4MakeTranslation(pos_.x, pos_.y, -0.1);
	sprite_->mvp_ = GLKMatrix4Multiply(he::g_Screen->projection_, tMat);
}

void RunningObject::Update(float dt){
	
	GLKVector2 newPos = GLKVector2Add(pos_, GLKVector2Multiply(dir_, speed_));
	if(newPos.x < -he::g_Screen->width_/2 || newPos.x > he::g_Screen->width_/2 || newPos.y < -he::g_Screen->height_/2 || newPos.y > he::g_Screen->height_/2){
		dir_ = GLKVector2Negate(dir_);
	}else{
		SetPosition(newPos);
	}
}

void RunningObject::Render(){
	sprite_->Render();
}
//EOF
