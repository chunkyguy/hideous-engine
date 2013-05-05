//
//  RectTextureTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 11/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "RectTextureTest.h"

#include <he/EventLoop/Gesture.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/RectTextureSh/RectTextureSh.h>
#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/Screen.h>
#include <he/Utils/Utils.h>
#include <he/Vertex/VertexTex.h>

RectTextureTest::~RectTextureTest(){
	unload_textures();
}

RectTextureTest::RectTextureTest(double w, double h){
		FILE_LOG(logDEBUG) <<"{" <<w << "," << h << "}";
		
		//setup globals
		//debugger
		const std::string loglevel("DEBUG1");
		FILELog::ReportingLevel() = FILELog::FromString(loglevel);
		FILE_LOG(logDEBUG) << "Logging Enabled: " << loglevel << std::endl;
		//random
		srand(time(NULL));
		//screen constants
		he::g_Screen = he::Screen(w, h);
		
		//start things here
		// waiting for input
}

void RectTextureTest::Update(double dt){
	handle_gestures();
}

void RectTextureTest::Render(){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	for(std::list<he::RenderObject *>::iterator it = render_objects_.begin(); it != render_objects_.end(); ++it){
		(*it)->Render();
	}
}

void RectTextureTest::load_textures(){
	if(!textures_.empty()){
		unload_textures();
	}
	
	GLKVector2 pos;
	GLKMatrix4 tMat;
	GLKMatrix4 mvpMat;
	he::VertexTex *v;
	shader_ = new he::RectTextureSh;
	
	//Draw a texture in proportion
	he::Texture *r1t = new he::Texture("texture","png");
	v = new he::VertexTex(200, 200);
	pos = GLKVector2Make(-150.0, 0.0);
	tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
	mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
	he::RenderObject *r = new he::RenderObject(v, shader_, r1t, mvpMat);
	render_objects_.push_back(r);
	textures_.push_back(r1t);
	vertex_datas_.push_back(v);
	
	//Draw a texture out of proportion
	he::Texture *r2t = new he::Texture("texture_alpha","png");
	v = new he::VertexTex(50, 25);
	pos = GLKVector2Make(-50.0, 0.0);
	tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
	mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
	he::RenderObject *r2 = new he::RenderObject(v, shader_, r2t, mvpMat);
	render_objects_.push_back(r2);
	textures_.push_back(r2t);
	vertex_datas_.push_back(v);
	
	//Draw a texture from atlas
	atlas_ = new he::TextureAtlas("tex_atlas","png");
	//fish
	for(int i = 0; i < 2; ++i){
		v = atlas_->createTextureData("fish", "png", 100, 100, i%2);
		GLKVector2 pos = GLKVector2Make(50.0, -100.0 + i*100.0);
		GLKMatrix4 tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
		GLKMatrix4 mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
		he::RenderObject *r3 = new he::RenderObject(v, shader_, atlas_->texture_, mvpMat);
		render_objects_.push_back(r3);
		vertex_datas_.push_back(v);
	}

	//rope
	v = atlas_->createTextureData("rope","png");
	pos = GLKVector2Make(150.0, 0.0);
	tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
	mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
	he::RenderObject *r4 = new he::RenderObject(v, shader_, atlas_->texture_, mvpMat);
	render_objects_.push_back(r4);
	vertex_datas_.push_back(v);
	
	//seaweed
	v = atlas_->createTextureData("seaweed","png");
	pos = GLKVector2Make(0.0, -100.0);
	tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
	mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
	he::RenderObject *r5 = new he::RenderObject(v, shader_, atlas_->texture_, mvpMat);
	render_objects_.push_back(r5);
	vertex_datas_.push_back(v);
}

void RectTextureTest::unload_textures(){
	for(std::list<he::RenderObject *>::iterator it = render_objects_.begin(); it != render_objects_.end(); ++it){
		delete *it;
	}
	render_objects_.clear();
	for(std::list<he::Texture *>::iterator it = textures_.begin(); it != textures_.end(); ++it){
		delete *it;
	}
	textures_.clear();
	for(std::list<he::VertexTex *>::iterator it = vertex_datas_.begin(); it != vertex_datas_.end(); ++it){
		delete *it;
	}
	vertex_datas_.clear();
	delete atlas_;
	delete shader_;
}

void RectTextureTest::handle_gestures(){
	if(he::g_Gesture.action_ == he::Gesture::kTap){
		load_textures();
		he::g_Gesture.Reset();
	}
}
//EOF