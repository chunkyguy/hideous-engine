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
position_(GLKVector2Make(-he::g_Screen.width_/2+he::Randf()*he::g_Screen.width_, -he::g_Screen.height_/2+he::Randf()*he::g_Screen.height_)),
sprite_(0),
life_state_(kLiving),
color_(GLKVector4Make(he::Randf(), he::Randf(), he::Randf(),he::Randf()))
{
	double dimension = he::Randf() * 40.0 + 2.0;
	vertex_data_ = new he::VertexCol(dimension/2, dimension/2);
	sprite_ = new he::RenderObject(vertex_data_, shader, 0, he::g_Screen.projection_, color_);
}

GLKVector2 RunningSquare::GetPosition(){
	return position_;
}

void RunningSquare::SetPosition(GLKVector2 p){
	position_ = p;
	GLKMatrix4 tMat = GLKMatrix4MakeTranslation(position_.x, position_.y, -0.1);
	mvp_ = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
}

RunningSquare::Life RunningSquare::GetLifeState(){
	return life_state_;
}

void RunningSquare::SetDead(){
	life_state_ = kDead;
}

void RunningSquare::Update(double dt){

	if(life_state_ != kLiving)
		return;
	
	GLKVector2 newPos = GLKVector2Add(position_, GLKVector2Multiply(direction_, speed_));
	if(newPos.x < -he::g_Screen.width_/2 || newPos.x > he::g_Screen.width_/2 || newPos.y < -he::g_Screen.height_/2 || newPos.y > he::g_Screen.height_/2){
		life_state_ = kZombie;
	}else{
		SetPosition(newPos);
	}
}

void RunningSquare::Render(){
	//sprite->setColor(color);
	sprite_->mvp_ = mvp_;
	sprite_->Render();
}
//EOF
