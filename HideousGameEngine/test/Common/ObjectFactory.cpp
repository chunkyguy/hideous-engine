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
#include <he/Shaders/ColorShader.h>
#include <he/Shaders/TextureShader.h>
#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Utils/Utils.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Vertex/ColorVertex.h>
#include <he/Vertex/TextureVertex.h>


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
	col_sh_ = new he::ColorShader;
	
	// texture obj
	texture_ = new he::Texture(he::ResourcePath() + "texture.png");
	vert_ = new he::TextureVertex(200, 200);
	atlas_ = new he::TextureAtlas( he::ResourcePath() + "tex_atlas.plist", he::ResourcePath() + "tex_atlas.png", he::TextureAtlas::Zwoptex);
	tex_sh_ = new he::TextureShader;
	
	// text obj
	font_ = new he::Font("Silom.ttf", 48);
	
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
ColObj::ColObj(he::ColorShader *shader){
	float dimension = he::Randf() * he::g_Screen->width_/2 + 10.0;
	vert_ = new he::ColorVertex(dimension/2, dimension/2);
	GLKVector4 color = GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 0.8);
	object_ = new he::RenderObject(vert_, shader, 0, he::g_Screen->projection_, color);
	transform_.SetPosition( GLKVector2Make(he::Randf()*he::g_Screen->width_ - he::g_Screen->width_/2, he::Randf()*he::g_Screen->height_ - he::g_Screen->height_/2));
}

void ColObj::Render(){
	object_->mvp_ = transform_.GetMVP();
	object_->Render();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	MARK: TextureObj
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureObj::~TextureObj(){
	delete object_;
}
TextureObj::TextureObj(he::TextureShader *shader, he::Texture *texture, 	he::TextureVertex *vert){
	object_ = new he::RenderObject(vert, shader, texture, he::g_Screen->projection_);
	transform_.SetPosition( GLKVector2Make(he::Randf()*he::g_Screen->width_ - he::g_Screen->width_/2, he::Randf()*he::g_Screen->height_ - he::g_Screen->height_/2) );
}
void TextureObj::Render(){
	object_->mvp_ = transform_.GetMVP();
	object_->Render();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	MARK: TextObj
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextObj::~TextObj(){
	delete text_;
}
TextObj::TextObj(he::Font *font){
	text_ = new he::Text("Whacky");
	font->LoadText(text_);
	transform_.SetPosition(GLKVector2Make(he::Randf()*he::g_Screen->width_ - he::g_Screen->width_/2, he::Randf()*he::g_Screen->height_ - he::g_Screen->height_/2));
}
void TextObj::Render(){
	text_->Render();
}
//EOF
