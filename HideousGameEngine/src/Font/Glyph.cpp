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
#include <he/Utils/Utils.h>
#include <he/Shaders/TextShader.h>

namespace he{

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Text::Glyph
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	Glyph::~Glyph(){
		he_Trace("~GlyphData\n");
		delete texture_;
		delete render_object_;
		delete vertex_data_;
	}
	
	Glyph::Glyph(std::string glyph_name, FT_GlyphSlot &glyph, GLKVector2 penPos, TextShader *shader, GLKVector4 color) :
	frame_(Frame((Transform_Create(GLKVector3Make(0.0f, 0.0f, 0.0f)))))
	{
		//FILE_LOG(logDEBUG) << "GlyphData" << std::endl;
		int w = NextPOT(glyph->bitmap.width);
		int h = NextPOT(glyph->bitmap.rows);
		
		size_ = GLKVector2Make(w, h);
		
		GLubyte *pixels = new GLubyte [2 * w * h];
		GLubyte *bp = pixels;
		for(int j=0; j <h; j++) {
			for(int i=0; i < w; i++){
				*bp = 0;
				if(i < glyph->bitmap.width && j < glyph->bitmap.rows){
					*bp = glyph->bitmap.buffer[i + glyph->bitmap.width*j];
				}
				bp++;
			}
		}
		
		GLKVector2 trans_pos = GLKVector2Make(penPos.x + glyph->bitmap_left, -penPos.y - glyph->bitmap_top);
		Transform_SetPosition(frame_.GetTransformPtr(), trans_pos);
		//		frame_.GetTransformPtr()->position = pos;
		//		GLKVector2 trans_pos = Transform_GetPosition(frame_.GetTransform());
		GLfloat p_data[] = {
			trans_pos.x,		-trans_pos.y,
			trans_pos.x+w,		-trans_pos.y,
			trans_pos.x,		-trans_pos.y-h,
			trans_pos.x+w,		-trans_pos.y-h
		};
		GLfloat t_data[] = {
			0, 0,
			1, 0,
			0, 1,
			1, 1
		};
		
		texture_ = new Texture(glyph_name, pixels, GLKVector2Make(w,h), 1);
		delete [] pixels;
		Vertex::V2 position_data;
		Vertex::Set(position_data, p_data);
		he_Trace("Glyph:%@\n%@\n%@\n",glyph_name,trans_pos,position_data);
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

	
}
///EOF
