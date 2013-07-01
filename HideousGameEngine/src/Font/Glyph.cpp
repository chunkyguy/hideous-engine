//
//  Glyph.cpp
//  HideousGameEngine
//
//  Created by Sid on 23/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Font/Glyph.h>

#include <he/RenderObject/RenderObject.h>
#include <he/Texture/Texture.h>
#include <he/Vertex/TextureVertex.h>
#include <he/Utils/DebugHelper.h>
#include <he/Shaders/TextShader.h>
#include <he/Utils/Utils.h>

static void PrintGlyph(GLubyte *data, int w, int h){
	for(int j=0; j <h; j++) {
		for(int i=0; i < w; i++){
			printf("%d",*data++==0?0:1);
			//			printf("%d",(*data++ == 0) ? 0 : 1 );
		}
		printf("\n");
	}
}

namespace he{

	GlyphData::GlyphData(char charctr, FT_GlyphSlot &glyph_slot, GLKVector3 pen_position) :
	ch(charctr),
	pen_pos(pen_position),
	size(Size(glyph_slot->bitmap.width, glyph_slot->bitmap.rows)),
	bearing(Size(glyph_slot->bitmap_left, glyph_slot->bitmap_top)),
	tex_size(Size(NextPOT(glyph_slot->bitmap.width), NextPOT(glyph_slot->bitmap.rows))),
	tex_data(nullptr)
	{
		tex_data = new GLubyte [2 * tex_size.w * tex_size.h];
		GLubyte *bp = tex_data;
		for(int j=0; j <tex_size.h; j++) {
			for(int i=0; i < tex_size.w; i++){
				*bp = 0;
				if(i < size.w && j < size.h){
					*bp = glyph_slot->bitmap.buffer[i + size.w*j];
				}
				bp++;
			}
		}
	}
	
	GlyphData::~GlyphData(){
		delete tex_data;
	}

	std::ostream &operator<<(std::ostream &os, const GlyphData::Size &sz){
		os << "{" << sz.w << "," << sz.h << "}";
		return os;
	}

	std::ostream &operator<<(std::ostream &os, const GlyphData &gd){
		PrintGlyph(gd.tex_data, gd.tex_size.w, gd.tex_size.h);
		os << "Char: " << gd.ch << std::endl;
		os << "Pen-position: " << gd.pen_pos << std::endl;
		os << "Size: " << gd.size << std::endl;
		os << "Bearing: " << gd.bearing << std::endl;
		os << "Tex-size: " << gd.tex_size;
		return os;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Text::Glyph
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	Glyph::~Glyph(){
		he_Trace("~GlyphData\n");
		delete texture_;
		delete render_object_;
		delete vertex_data_;
	}
	
	Glyph::Glyph(Frame frame, GlyphData *data, TextShader *shader, GLKVector4 color) :
	View(frame)
	{
//		GLKVector3 trans_pos = GetFrame().GetTransform().position;
//		trans_pos.x = trans_pos.x + glyph->bitmap_left;
//		trans_pos.y = -trans_pos.y - glyph->bitmap_top;
//		GetFramePtr()->GetTransformPtr()->position = trans_pos;
//GLKVector2 trans_pos = GLKVector2Make(glyph->bitmap_left, glyph->bitmap_top);
		GLKVector2 trans_pos = frame.GetSize();
		GLfloat p_data[] = {
			-trans_pos.x/2.0f,	-trans_pos.y/2.0f,
			trans_pos.x/2.0f,	-trans_pos.y/2.0f,
			-trans_pos.x/2.0f,	trans_pos.y/2.0f,
			trans_pos.x/2.0f,	trans_pos.y/2.0f
		};
		
		GLfloat s = static_cast<GLfloat>(data->size.w)/static_cast<GLfloat>(data->tex_size.w);
		GLfloat t = static_cast<GLfloat>(data->size.h)/static_cast<GLfloat>(data->tex_size.h);
		GLfloat t_data[] = {
			0.0f,	t,
			s,		t,
			0.0f,	0.0f,
			s,		0.0f
		};
		
		texture_ = new Texture(std::string(1, data->ch), data->tex_data, GLKVector2Make(data->tex_size.w, data->tex_size.h), 1);
		Vertex::V2 position_data;
		Vertex::Set(position_data, p_data);
		//		he_Trace("Glyph:%@\n%@\n%@\n%@\n",glyph_name,trans_pos,frame.GetSize(),position_data);
		Vertex::V2 texture_data;
		Vertex::Set(texture_data, t_data);
		vertex_data_ = new TextureVertex(position_data, texture_data);
		render_object_ = new RenderObject(vertex_data_, shader, texture_, GLKMatrix4Identity, color);
	}
	
	//	void GlyphData::Render(){
	//		GLfloat box[] = {
	//			x,		-y,		0, 0,
	//			x+w,		-y,		1, 0,
	//			x,		-y-h,	0, 1,
	//			x+w,		-y-h,	1, 1
	//		};
	//
	//		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, w, h, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);
	//		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
	//		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//	}


	void Glyph::update(float dt){
		render_object_->SetMVP(Transform_GetMVP(&(GetFrame().GetTransform())));
	}
	
	void Glyph::render(){
		render_object_->Render();
	}
	
}
///EOF