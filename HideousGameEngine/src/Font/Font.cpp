//
//  Font.cpp
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Font/Font.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/RectTextSh/RectTextSh.h>
#include <he/Texture/Texture.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Utils.h>
#include <he/Vertex/VertexTex.h>

namespace he{
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Font
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	Font::~Font(){
		delete shader_;
		FT_Done_Face(face_);
	}
	Font::Font(std::string name, unsigned int size) :
	name_(name)
	{
		FILE_LOG(logDEBUG) << "loading font: " << name;
		
		std::string fontPath = ResourcePath() + name;
		FT_Error error = FT_New_Face(GetLibrary()->object_, fontPath.c_str(), 0, &face_);
		assert(error != FT_Err_Unknown_File_Format);		//"Font format not supported"
		assert(!error); // "Unable to open font"
		FT_Set_Pixel_Sizes(face_, 0, size);
		
		shader_ = new RectTextSh;
	}
	
	void Font::LoadText(Text *text){
		///Create new
		GLKVector2 pen_position = GLKVector2Make(0,0);
		int pos = 0;
		for(std::string::iterator it = text->string_.begin(); it != text->string_.end(); ++it){
			const char ch = *it;
			if(FT_Load_Char(face_, ch, FT_LOAD_RENDER)){
				FILE_LOG(logERROR) << "Couldn't load char : " << *it;
			}
			FT_GlyphSlot glyph_slot = (face_)->glyph;
		
			Text::Glyph *g = new Text::Glyph(name_, std::string(1, ch), glyph_slot, pen_position, shader_, text->color_);
			
			// For Some Twisted Reason, FreeType Measures Font Size
			// In Terms Of 1/64ths Of Pixels.  Thus, To Make A Font
			//Advance for next char.. if looping
			pen_position.x += (glyph_slot->advance.x >> 6);
			pen_position.y += (glyph_slot->advance.y >> 6);
			
			text->data_[pos++] = g;
		}
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

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Text
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	Text::Text(std::string string, Transform transform, 	GLKVector4 color) :
	string_(string),
	transform_(transform),
	color_(color)
	{
		data_ = new Glyph *[string_.size()];
	}
	
	Text::~Text(){
		for(int i = 0; i < string_.size(); ++i){
			delete data_[i];
		}
		delete [] data_;
	}
	
	void Text::Render(){
		for(int i = 0; i < string_.size(); ++i){
			he::RenderObject *object = data_[i]->render_object_;
			object->mvp_ = transform_.GetMVP();
			object->Render();
		}
	}
	
	void Text::SetTransform(Transform transform){
		transform_ = transform;
	}
	
	const Transform &Text::GetTransform() const{
		return transform_;
	}
	
	GLKVector2 Text::GetSize(){
		GLKVector2 size = GLKVector2Make(0,0);
		for(int i = 0; i < string_.size(); ++i){
			GLKVector2 it_sz = data_[i]->size_;
			size.x += it_sz.x;
			size.y = (size.y > it_sz.y) ? size.y: it_sz.y;
		}
		return size;
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Text::Glyph
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	Text::Glyph::~Glyph(){
		FILE_LOG(logDEBUG) << "~GlyphData" << std::endl;
		delete texture_;
		delete render_object_;
		delete vertex_data_;
	}
	
	Text::Glyph::Glyph(std::string font_name, std::string char_name, FT_GlyphSlot &glyph, GLKVector2 penPos, RectTextSh *shader, GLKVector4 color)
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
		
		transform_.position_ = GLKVector2Make(penPos.x + glyph->bitmap_left, -penPos.y - glyph->bitmap_top);
		GLfloat p_data[] = {
			transform_.position_.x,		-transform_.position_.y,
			transform_.position_.x+w,	-transform_.position_.y,
			transform_.position_.x,		-transform_.position_.y-h,
			transform_.position_.x+w,	-transform_.position_.y-h
		};
		GLfloat t_data[] = {
			0, 0,
			1, 0,
			0, 1,
			1, 1
		};
		
		texture_ = new Texture(font_name + char_name, pixels, GLKVector2Make(w,h), 1);
		delete [] pixels;
		VertexData position_data = VertexData(p_data);
		VertexData texture_data = VertexData(t_data);
		vertex_data_ = new VertexTex(position_data, texture_data);
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