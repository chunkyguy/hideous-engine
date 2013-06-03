//
//  RunningSquare.cpp
//  HideousGameEngine
//
//  Created by Sid on 10/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "RunningSquare.h"

#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/RectColorSh/RectColorSh.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Screen.h>
#include <he/Utils/Utils.h>
#include <he/Vertex/VertexCol.h>

RunningSquare::~RunningSquare(){
	delete sprite_;
	delete vertex_data_;
}

RunningSquare::RunningSquare(he::RectColorSh *shader) :
speed_(GLKVector2Make(0.1 + he::Randf()*5.0, 0.1 + he::Randf()*5.0)),
direction_(GLKVector2Make(rand()%2?-1:1, rand()%2?-1:1)),
sprite_(0),
life_state_(kLiving),
color_(GLKVector4Make(he::Randf(), he::Randf(), he::Randf(),he::Randf()))
{
	float dimension = he::Randf() * 40.0 + 2.0;
	vertex_data_ = new he::VertexCol(dimension/2, dimension/2);
	sprite_ = new he::RenderObject(vertex_data_, shader, 0, he::g_Screen->projection_, color_);
	transform_.position_ = GLKVector2Make(-he::g_Screen->width_/2+he::Randf()*he::g_Screen->width_, -he::g_Screen->height_/2+he::Randf()*he::g_Screen->height_);
}

RunningSquare::Life RunningSquare::GetLifeState(){
	return life_state_;
}

void RunningSquare::SetDead(){
	life_state_ = kDead;
}

void RunningSquare::Update(float dt){

	if(life_state_ != kLiving)
		return;
	
	GLKVector2 newPos = GLKVector2Add(transform_.GetPosition(), GLKVector2Multiply(direction_, speed_));
	if(newPos.x < -he::g_Screen->width_/2 || newPos.x > he::g_Screen->width_/2 || newPos.y < -he::g_Screen->height_/2 || newPos.y > he::g_Screen->height_/2){
		life_state_ = kZombie;
	}else{
		transform_.SetPosition(newPos);
	}
}

void RunningSquare::Render(){
	//sprite->setColor(color);
	sprite_->mvp_ = transform_.GetMVP();
	sprite_->Render();
}
//EOF
