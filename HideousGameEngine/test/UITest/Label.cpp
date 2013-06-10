//
//  Label.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "Label.h"

#include <he/Font/Font.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Utils/Utils.h>
#include <he/Utils/Screen.h>
#include <he/Vertex/ColorVertex.h>

Label::Label(std::string string, he::Font *font) :
font_(font),
text_(new he::Text(string))
{
	font_->LoadText(text_);
}

Label::~Label(){
	delete text_;
}

void Label::SetText(std::string string){
	if(text_){
		delete text_;
	}
	text_ = new he::Text(string);
	font_->LoadText(text_);
}

he::ColorVertex Label::GetBox(){
	GLKVector2 size = text_->GetSize();
	return he::ColorVertex(text_->transform_.position_.x, text_->transform_.position_.y,
						 text_->transform_.position_.x + size.x, text_->transform_.position_.y + size.y);
}

void Label::SetColor(GLKVector4 clr){
	text_->color_ = clr;
}

void Label::Render(){
	text_->SetTransform(transform_);
	text_->Render();
}


///EOF
