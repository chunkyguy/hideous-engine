//
//  ObjectFactory.cpp
//  HEAssets
//
//  Created by Sid on 28/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "ObjectFactory.h"


#include <he/Font/Font.h>
#include <he/UI/Text.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/ColorShader.h>
#include <he/Shaders/TextShader.h>
#include <he/Shaders/TextureShader.h>
#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Utils.h>
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
	return new TextObj(txt_factory_);
}

void ObjectFactory::load_assets(){
	col_sh_ = new he::ColorShader;
	
	// texture obj
	texture_ = new he::Texture(he::ResourcePath() + "texture.png");
	GLKVector2 size = GLKVector2Make(200, 200);
	vert_ = new he::TextureVertex(size);
	atlas_ = new he::TextureAtlas( he::ResourcePath() + "tex_atlas.plist", he::ResourcePath() + "tex_atlas.png", he::TextureAtlas::kZwoptex);
	tex_sh_ = new he::TextureShader;
	
	// text obj
	txt_sh_ = new he::TextShader;
	txt_factory_ = new he::TextViewFactory(txt_sh_,new he::Font(he::ResourcePath() + "Silom.ttf", 48));
}
void ObjectFactory::unload_assets(){
	delete col_sh_;

	delete texture_;
	delete vert_;
	delete atlas_;
	delete tex_sh_;
	
	delete txt_sh_;
	delete txt_factory_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	MARK: ColObj
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ColObj::~ColObj(){
	delete vert_;
	delete object_;
}
ColObj::ColObj(he::ColorShader *shader){
	transform_ = he::Transform_Create(GLKVector2Make(0.0f, 0.0f));
	float dimension = he::Randf() * he::g_Screen->width_/2 + 10.0;
	he::ColorVertex::Data min = {GLKVector2Make(-dimension/2.0f, -dimension/2.0f), GLKVector4Make(1.0, 0.0, 0.0, 1.0)};
	he::ColorVertex::Data max = {GLKVector2Make(dimension/2.0f, dimension/2.0f), GLKVector4Make(0.0, 1.0, 0.0, 1.0)};

	vert_ = new he::ColorVertex(min, max);
	GLKVector4 color = GLKVector4Make(he::Randf(), he::Randf(), he::Randf(), 0.8);
	object_ = new he::RenderObject(vert_, shader, 0, he::g_Screen->projection_, color);
	transform_.position = GLKVector3Make(he::Randf()*he::g_Screen->width_ - he::g_Screen->width_/2, he::Randf()*he::g_Screen->height_ - he::g_Screen->height_/2, he::g_Screen->z_);
}

void ColObj::Render(){
	object_->mvp_ = he::Transform_GetMVP(&transform_);
	object_->Render();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	MARK: TextureObj
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureObj::~TextureObj(){
	delete object_;
}
TextureObj::TextureObj(he::TextureShader *shader, he::Texture *texture, he::TextureVertex *vert){
	transform_ = he::Transform_Create(GLKVector2Make(he::Randf()*he::g_Screen->width_ - he::g_Screen->width_/2, he::Randf()*he::g_Screen->height_ - he::g_Screen->height_/2));
	object_ = new he::RenderObject(vert, shader, texture, he::g_Screen->projection_);
}
void TextureObj::Render(){
	object_->mvp_ = he::Transform_GetMVP(&transform_);
	object_->Render();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	MARK: TextObj
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextObj::~TextObj(){
	delete text_;
}

TextObj::TextObj(he::TextViewFactory *factory){
	text_ = factory->CreateTextView(he::Transform_Create(GLKVector2Make(he::Randf()*he::g_Screen->width_ - he::g_Screen->width_/2, he::Randf()*he::g_Screen->height_ - he::g_Screen->height_/2)), "WhackyLabs");
}
void TextObj::Update(float dt){
	text_->Update(dt);
}
void TextObj::Render(){
	text_->Render();
}
//EOF
