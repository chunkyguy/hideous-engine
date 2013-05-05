//
//  GObj.cpp
//  HideousGameEngine
//
//  Created by Sid on 25/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "GObj.h"

#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/RectColorSh/RectColorSh.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Screen.h>
#include <he/Vertex/VertexCol.h>


GObj::~GObj(){
	delete render_object_;
	delete vert_;
	delete shader_;
}

GObj::GObj() :
direction_(GLKVector2Make(0,0)),
vert_(new he::VertexCol(-10, 10)),
shader_(new he::RectColorSh),
color_( GLKVector4Make(1.0, 1.0, 1.0, 1.0)),
position_(GLKVector2Make(0, 0))
{
	render_object_ = new he::RenderObject(vert_, shader_, 0, he::g_Screen.projection_, color_);
}

void GObj::Update(double dt){
	position_ = GLKVector2Add(position_, GLKVector2MultiplyScalar(direction_, kSpeed));
	render_object_->mvp_ = GLKMatrix4Multiply(he::g_Screen.projection_, GLKMatrix4MakeTranslation(position_.x, position_.y, -0.5));
	render_object_->color_ = GLKVector4Make(color_.r, color_.g, color_.b, color_.a);
}

void GObj::Render(){
	render_object_->Render();
}

void GObj::SetPosition(GLKVector2 newPos){
	position_ = newPos;
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
