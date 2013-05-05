//
//  TexturedSprite.cpp
//  HideousGameEngine
//
//  Created by Sid on 04/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "TexturedSprite.h"

#include <he/RenderObject/RenderObject.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Screen.h>
#include <he/Utils/Utils.h>

TexturedSprite::~TexturedSprite(){
	//don't delete sprite! Owned by Kalchakra.
}

TexturedSprite::TexturedSprite() :
speed_(GLKVector2Make(0.1 + he::Randf()*5.0, 0.1 + he::Randf()*5.0)),
direction_(GLKVector2Make(rand()%2?-1:1, rand()%2?-1:1)),
//position_(GLKVector2Make(-he::g_Screen.width/2+he::Randf()*he::g_Screen.width, -he::g_Screen.height/2+he::Randf()*he::g_Screen.height)),
sprite_(0),
life_state_(kLiving){
}

bool TexturedSprite::Init(int iD, he::RenderObject *sp, GLKVector2 at){
	ID_ = iD;
	sprite_ = sp;
	position_ = at;
	return true;
}

void TexturedSprite::Update(double dt){
	if(life_state_ != kLiving)
		return;

	//setPos(position_);

	GLKVector2 newPos = GLKVector2Add(position_, GLKVector2Multiply(direction_, speed_));
	if(newPos.x < -he::g_Screen.width_/2 || newPos.x > he::g_Screen.width_/2 || newPos.y < -he::g_Screen.height_/2 || newPos.y > he::g_Screen.height_/2){
		life_state_ = kZombie;
	}else{
		SetPosition(newPos);
	}
}

GLKVector2 TexturedSprite::GetPosition(){
	return position_;
}

void TexturedSprite::SetPosition(GLKVector2 p){
	//FILE_LOG(logDEBUG) << ID << "{" << p.x << "," << p.y << "}";
	position_ = p;
	GLKMatrix4 tMat = GLKMatrix4MakeTranslation(position_.x, position_.y, -0.1);
	GLKMatrix4 mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
	sprite_->mvp_ = mvpMat;
}
TexturedSprite::Life TexturedSprite::GetLifeState(){
	return life_state_;
}
void TexturedSprite::SetDead(){
	life_state_ = kDead;
}

///EOF

