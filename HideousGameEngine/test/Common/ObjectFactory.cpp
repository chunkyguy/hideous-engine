//
//  ObjectFactory.cpp
//  HEAssets
//
//  Created by Sid on 28/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "ObjectFactory.h"

#include <he/Font/Font.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/RectColorSh/RectColorSh.h>
#include <he/Shaders/RectTextureSh/RectTextureSh.h>
#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Utils/Screen.h>
#include <he/Utils/Utils.h>
#include <he/Vertex/VertexCol.h>
#include <he/Vertex/VertexTex.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	MARK: ObjectFactory
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ObjectFactory::~ObjectFactory(){
	unload_assets();
}
ObjectFactory::ObjectFactory(){
	load_assets();
}

ColObj *ObjectFactory::CreateColoredObject(){
	return new ColObj(col_sh_);
}
TextureObj *ObjectFactory::CreateTexturedObject(){
	
	return new TextureObj(tex_sh_, texture_, vert_);
}
TextObj *ObjectFactory::CreateTextObject(){
	return new TextObj(font_);
}

void ObjectFactory::load_assets(){
	col_sh_ = new he::RectColorSh;
	
	// texture obj
	texture_ = new he::Texture("texture","png");
	vert_ = new he::VertexTex(200, 200);
	atlas_ = new he::TextureAtlas("tex_atlas","png");
	tex_sh_ = new he::RectTextureSh;
	
	// text obj
	font_ = new he::Font("Silom.ttf", 48, GLKVector4Make(0.0, 0.0, 0.0, 1.0));
	
}
void ObjectFactory::unload_assets(){
	delete col_sh_;

	delete texture_;
	delete vert_;
	delete atlas_;
	delete tex_sh_;
	
	delete font_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	MARK: ColObj
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ColObj::~ColObj(){
	delete vert_;
	delete object_;
}
ColObj::ColObj(he::RectColorSh *shader){
	double dimension = he::Randf() * he::g_Screen.width_/2 + 10.0;
	vert_ = new he::VertexCol(dimension/2, dimension/2);
	GLKVector4 color = GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), he::Randf());
	object_ = new he::RenderObject(vert_, shader, 0, he::g_Screen.projection_, color);
	pos_ = GLKVector2Make(he::Randf()*he::g_Screen.width_ - he::g_Screen.width_/2, he::Randf()*he::g_Screen.height_ - he::g_Screen.height_/2);
}
void ColObj::Render(){
	GLKMatrix4 tMat;
	GLKMatrix4 mvpMat;

	tMat = GLKMatrix4MakeTranslation(pos_.x, pos_.y, -0.1);
	mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
	object_->mvp_ = mvpMat;

	object_->Render();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	MARK: TextureObj
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureObj::~TextureObj(){
	delete object_;
}
TextureObj::TextureObj(he::RectTextureSh *shader, he::Texture *texture, 	he::VertexTex *vert){
	object_ = new he::RenderObject(vert, shader, texture, he::g_Screen.projection_);
	pos_ = GLKVector2Make(he::Randf()*he::g_Screen.width_ - he::g_Screen.width_/2, he::Randf()*he::g_Screen.height_ - he::g_Screen.height_/2);
}
void TextureObj::Render(){
	GLKMatrix4 tMat;
	GLKMatrix4 mvpMat;

	tMat = GLKMatrix4MakeTranslation(pos_.x, pos_.y, -0.1);
	mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
	object_->mvp_ = mvpMat;

	object_->Render();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	MARK: TextObj
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextObj::~TextObj(){
}
TextObj::TextObj(he::Font *font){
	font->LoadGlyph("Whacky?!");
	glyph_data_ = font->GetGlyph();
	pos_ = GLKVector2Make(he::Randf()*he::g_Screen.width_ - he::g_Screen.width_/2, he::Randf()*he::g_Screen.height_ - he::g_Screen.height_/2);
}
void TextObj::Render(){
	GLKMatrix4 tMat;
	GLKMatrix4 mvpMat;
	
	for(std::list<he::GlyphData *>::iterator it = glyph_data_.begin(); it != glyph_data_.end(); ++it){
		he::RenderObject *object = (*it)->render_object_;
		//pos = (*it)->position;
		tMat = GLKMatrix4MakeTranslation(pos_.x, pos_.y, -0.1);
		mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
		object->mvp_ = mvpMat;
		//r->clr = GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 1.0);	// Epilepsy warning
		object->Render();
	}
}
//EOF
