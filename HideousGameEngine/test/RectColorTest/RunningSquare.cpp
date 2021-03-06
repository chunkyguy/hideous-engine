//
//  RunningSquare.cpp
//  HideousGameEngine
//
//  Created by Sid on 10/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "RunningSquare.h"

#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/ColorShader.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Screen.h>
#include <he/Utils/Utils.h>
#include <he/Utils/DebugHelper.h>
#include <he/Vertex/ColorVertex.h>

RunningSquare::~RunningSquare(){
	delete sprite_;
	delete vertex_data_;
}

RunningSquare::RunningSquare(he::ColorShader *shader) :
speed_(GLKVector2Make(0.1 + he::Randf(0.1, 1.0), he::Randf(0.1, 1.0))),
direction_(GLKVector2Make(rand()%2?-1:1, rand()%2?-1:1)),
sprite_(0),
life_state_(kLiving),
color_(GLKVector4Make(he::Randf(), he::Randf(), he::Randf(),he::Randf()))
{
	transform_ = he::Transform_Create(GLKVector2Make(0.0f, 0.0f));
	float width = he::Randf(70.0, 100.0);
	float height = he::Randf(70.0, 100.0);
	he::ColorVertex::Data min = {GLKVector2Make(-width/2.0f, -height/2.0f), GLKVector4Make(he::Randf(0.0f, 1.0f), he::Randf(0.0f, 1.0f), he::Randf(0.0f, 1.0f), 1.0)};
	he::ColorVertex::Data max = {GLKVector2Make(width/2.0f, height/2.0f), GLKVector4Make(he::Randf(0.0f, 1.0f), he::Randf(0.0f, 1.0f), he::Randf(0.0f, 1.0f), 1.0)};
	he_Trace("RectColorTest: \nmin = %@\nmax = %@\n",min.color,max.color);
	vertex_data_ = new he::ColorVertex(min, max);

	sprite_ = new he::RenderObject(vertex_data_, shader, 0, he::g_Screen->projection_, color_);
	he::Transform_SetPosition(&transform_, GLKVector2Make(-he::g_Screen->width_/2+he::Randf()*he::g_Screen->width_, -he::g_Screen->height_/2+he::Randf()*he::g_Screen->height_) );
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
	
	GLKVector2 pos_incr = direction_ * speed_;
	GLKVector2 newPos = he::Transform_GetPosition(transform_) + pos_incr;
	if(newPos.x < -he::g_Screen->width_/2 || newPos.x > he::g_Screen->width_/2 || newPos.y < -he::g_Screen->height_/2 || newPos.y > he::g_Screen->height_/2){
		life_state_ = kZombie;
	}else{
		he::Transform_SetPosition(&transform_, newPos);
	}
}

void RunningSquare::Render(){
	//sprite->setColor(color);
	sprite_->mvp_ = Transform_GetMVP(&transform_);
	sprite_->Render();
}
//EOF
