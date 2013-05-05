//
//  Font.cpp
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Font/Font.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Utils.h>
#include <he/Vertex/VertexTex.h>
#include <he/Texture/Texture.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/RectTextSh/RectTextSh.h>

namespace he{
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: GlyphData
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	GlyphData::~GlyphData(){
		FILE_LOG(logDEBUG) << "~GlyphData" << std::endl;
		delete texture_;
		delete render_object_;
		delete vertex_data_;
	}
	
	GlyphData::GlyphData(std::string font_name, std::string char_name, FT_GlyphSlot &glyph, GLKVector2 penPos, RectTextSh *shader, GLKVector4 color)
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
		
		position_ = GLKVector2Make(penPos.x + glyph->bitmap_left, -penPos.y - glyph->bitmap_top);
		GLfloat p_data[] = {
			position_.x,		-position_.y,
			position_.x+w,	-position_.y,
			position_.x,		-position_.y-h,
			position_.x+w,	-position_.y-h
		};
		GLfloat t_data[] = {
			0, 0,
			1, 0,
			0, 1,
			1, 1
		};
		
		texture_ = new Texture(font_name, char_name, pixels, GLKVector2Make(w,h), 1);
		delete [] pixels;
		vertex_data_ = new VertexTex(0, 0);
		vertex_data_->position_data_ = VertexData(p_data);
		vertex_data_->texture_data_ = VertexData(t_data);
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
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Font
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	Font::~Font(){
		if(!glyph_data_.empty()){
			UnloadGlyph();
		}
		delete shader_;
		FT_Done_Face(face_);
	}
	Font::Font(std::string name, unsigned int size, GLKVector4 color) :
	name_(name),
	color_(color)
	{
		FILE_LOG(logDEBUG) << "loading font: " << name;
		
		std::string fontPath = ResourcePath() + name;
		FT_Error error = FT_New_Face(GetLibrary()->object_, fontPath.c_str(), 0, &face_);
		assert(error != FT_Err_Unknown_File_Format);		//"Font format not supported"
		assert(!error); // "Unable to open font"
		FT_Set_Pixel_Sizes(face_, 0, size);
		
		shader_ = new RectTextSh;
	}
	
	void Font::LoadGlyph(std::string text, GLKVector2 penPosition){
		//Delete
		if(!glyph_data_.empty()){
			UnloadGlyph();
		}
		
		///Create new
		for(std::string::iterator it = text.begin(); it != text.end(); ++it){
			const char ch = *it;
			if(FT_Load_Char(face_, ch, FT_LOAD_RENDER)){
				FILE_LOG(logERROR) << "Couldn't load char : " << *it;
			}
			FT_GlyphSlot glyph = (face_)->glyph;
		
			GlyphData *g = new GlyphData(name_, std::string(1, ch), glyph, penPosition, shader_, color_);
			
			// For Some Twisted Reason, FreeType Measures Font Size
			// In Terms Of 1/64ths Of Pixels.  Thus, To Make A Font
			//Advance for next char.. if looping
			penPosition.x += (glyph->advance.x >> 6);
			penPosition.y += (glyph->advance.y >> 6);
			
			glyph_data_.push_back(g);
		}
	}
	void Font::UnloadGlyph(){
		for(std::list<GlyphData *>::iterator it = glyph_data_.begin(); it != glyph_data_.end(); ++it){
			delete *it;
		}
		glyph_data_.clear();
	}
	std::list<GlyphData *> &Font::GetGlyph(){
		return glyph_data_;
	}
	
	Font::Library *Font::library_ = 0;
	Font::Library *Font::GetLibrary(){
		if(!library_){
			library_ = new Library;
			atexit(&CleanLibrary);
		}
		return library_;
	}
	void Font::CleanLibrary(){
		delete library_; library_ = 0;
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: FontLib
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	Font::Library::~Library(){
		FT_Done_FreeType(object_);
	}
	Font::Library::Library(){
		FT_Error error = FT_Init_FreeType(&object_);
		assert(!error);
	}
	
}