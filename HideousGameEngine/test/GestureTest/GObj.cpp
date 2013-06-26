//
//  GObj.cpp
//  HideousGameEngine
//
//  Created by Sid on 25/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "GObj.h"

#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/ColorShader.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Screen.h>
#include <he/Vertex/ColorVertex.h>


GObj::~GObj(){
	delete render_object_;
	delete vert_;
	delete shader_;
}

GObj::GObj() :
direction_(GLKVector2Make(0,0)),
vert_(),
shader_(new he::ColorShader),
color_( GLKVector4Make(1.0, 1.0, 1.0, 1.0))
{
	transform_ = he::Transform_Create(GLKVector2Make(0.0f, 0.0f));
	float dimension = 20.0f;
	he::ColorVertex::Data min = {GLKVector2Make(-dimension/2.0f, -dimension/2.0f), GLKVector4Make(1.0, 0.0, 0.0, 1.0)};
	he::ColorVertex::Data max = {GLKVector2Make(dimension/2.0f, dimension/2.0f), GLKVector4Make(0.0, 1.0, 0.0, 1.0)};
	
	vert_ = new he::ColorVertex(min, max);

	render_object_ = new he::RenderObject(vert_, shader_, 0, he::g_Screen->projection_, color_);
}

void GObj::Update(float dt){
	transform_.position = transform_.position + GLKVector3Make(direction_.x, direction_.y, 0.0f) * kSpeed;
	render_object_->mvp_ = Transform_GetMVP(&transform_);
	render_object_->color_ = GLKVector4Make(color_.r, color_.g, color_.b, color_.a);
}

void GObj::Render(){
	render_object_->Render();
}

void GObj::SetTransform(he::Transform transform){
	transform_ = transform;
}
void GObj::SetColor(GLKVector4 newClr){
	color_ = newClr;
}
void GObj::SetDirection(he::Screen::Grid grid_point){
	switch(grid_point){
		case he::Screen::Grid::kTopLeft:		direction_.x = -1; direction_.y = 1; break;
		case he::Screen::Grid::kTop:			direction_.x = 0; direction_.y = 1; break;
		case he::Screen::Grid::kTopRight:		 direction_.x = 1; direction_.y = 1; break;
		case he::Screen::Grid::kLeft:			 direction_.x = -1; direction_.y = 0; break;
		case he::Screen::Grid::kCenter:		 direction_.x = 0; direction_.y = 0; break;
		case he::Screen::Grid::kRight:			 direction_.x = 1; direction_.y = 0; break;
		case he::Screen::Grid::kBottomLeft:	 direction_.x = -1; direction_.y = -1; break;
		case he::Screen::Grid::kBottom:		 direction_.x = 0; direction_.y = -1; break;
		case he::Screen::Grid::kBottomRight:	 direction_.x = 1; direction_.y = -1; break;
		case he::Screen::Grid::kUnknown:		 direction_.x = 0; direction_.y = 0; break;
	}
}
///EOF
