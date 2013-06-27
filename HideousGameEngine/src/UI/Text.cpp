//
//  Text.cpp
//  HideousGameEngine
//
//  Created by Sid on 23/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/Text.h>

#include <he/RenderObject/RenderObject.h>
#include <he/Font/Font.h>
#include <he/Font/Glyph.h>
#include <he/Shaders/TextShader.h>
#include <he/Utils/DebugHelper.h>

namespace he{
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Text
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	Text::Text(Frame frame, TextFactory *factory, std::string string, GLKVector4 color) :
	View(frame)
	{
		data_len_ = string.size();
		data_ = new Glyph *[data_len_];
		
		eff_size_ = GLKVector2Make(0,0);
		GLKVector2 pen_position = GLKVector2Make(0,0);
		int pos = 0;
		const FT_Face face = factory->font.Get()->GetFace();
		for(std::string::iterator it = string.begin(); it != string.end(); ++it){
			const char ch = *it;
			FT_Error ret = FT_Load_Char(face, ch, FT_LOAD_RENDER);
			assert(ret == 0); //"Couldn't load char
			FT_GlyphSlot glyph_slot = face->glyph;
			
			Glyph *g = new Glyph(std::string(1, ch), glyph_slot, pen_position, factory->shader.Get(), color);
			
			// For Some Twisted Reason, FreeType Measures Font Size
			// In Terms Of 1/64ths Of Pixels.  Thus, To Make A Font
			//Advance for next char.. if looping
			pen_position.x += (glyph_slot->advance.x >> 6);
			pen_position.y += (glyph_slot->advance.y >> 6);
			
			data_[pos++] = g;
			
			GLKVector2 it_sz = g->size_;
			eff_size_.x += it_sz.x;
			eff_size_.y = (eff_size_.y > it_sz.y) ? eff_size_.y: it_sz.y;
		}
		he_Trace("Text:eff_size: %@\n",eff_size_);
	}
	
	Text::~Text(){
		for(int i = 0; i < data_len_; ++i){
			delete data_[i];
		}
		delete [] data_;
	}

	void Text::update(float dt){
		for(int i = 0; i < data_len_; ++i){
			he::RenderObject *object = data_[i]->render_object_;
			object->SetMVP(Transform_GetMVP(&(GetFrame().GetTransform())));
		}
	}
	void Text::render(){
		for(int i = 0; i < data_len_; ++i){
			he::RenderObject *object = data_[i]->render_object_;
			object->Render();
		}
	}
		
	GLKVector2 Text::GetActualSize() const{
		return eff_size_;
	}

	
	TextFactory::TextFactory(Font *fnt, TextShader *sh){
		font.Set(fnt, true);
		shader.Set(sh, true);
	}

}
///EOF
