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
#include <he/Vertex/VertexCol.h>

Label::Label(std::string text, he::Font *font) :
font_(font),
text_(text),
size_(GLKVector2Make(0,0))
{ }

void Label::SetText(std::string text){
	text_ = text;
}

he::VertexCol Label::GetBox(){
	return he::VertexCol(transform_.GetPosition().x, transform_.GetPosition().y, transform_.GetPosition().x + size_.x, transform_.GetPosition().y + size_.y);
}

void Label::SetColor(GLKVector4 clr){
	font_->color_ = clr;
}

void Label::Render(){
	GLKMatrix4 tMat;
	GLKMatrix4 mvpMat;
	GLKVector2 pos = transform_.GetPosition();
	size_ = GLKVector2Make(0,0);

	font_->LoadGlyph(text_);
	std::list<he::GlyphData *>gd = font_->GetGlyph();
	for(std::list<he::GlyphData *>::iterator it = gd.begin(); it != gd.end(); ++it){
		size_ = GLKVector2Add(size_, (*it)->size_);
		he::RenderObject *object = (*it)->render_object_;
		tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
		mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
		object->mvp_ = mvpMat;
		object->Render();
	}
}


///EOF
