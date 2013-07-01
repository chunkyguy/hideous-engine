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
#include <he/Utils/Utils.h>

namespace he{
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Text
	/////////////////////////////////////////////////////////////////////////////////////////////////////
//	Text::Text(Frame frame, Glyph **data_m, unsigned int data_len, GLKVector4 color) :
//	View(frame),
//	data_(data_m),
//	data_len_(data_len)
//	{	}
//	
//	Text::~Text(){
//		for(int i = 0; i < data_len_; ++i){
//			delete data_[i];
//		}
//		delete [] data_;
//	}
//
//	void Text::update(float dt){
//		for(int i = 0; i < data_len_; ++i){
//			he::RenderObject *object = data_[i]->render_object_;
//			object->SetMVP(Transform_GetMVP(&(GetFrame().GetTransform())));
//		}
//	}
//	void Text::render(){
//		for(int i = 0; i < data_len_; ++i){
//			he::RenderObject *object = data_[i]->render_object_;
//			object->Render();
//		}
//	}
//		
//	GLKVector2 Text::GetActualSize() const{
//		return eff_size_;
//	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: TextFactory
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TextFactory::TextFactory(TextShader *shdr, Font *fnt_m){
		shader.Set(shdr, true);
		font.Move(fnt_m, true);
	}

	Text *TextFactory::CreateText(Transform transform, std::string string, GLKVector4 color){
		Text *txt = new Text(Frame(transform));
		
		const FT_Face face = font.Get()->GetFace();
		GlyphData **gdata = new GlyphData* [string.size()];
		// create textures
		GLKVector3 pen_position = GLKVector3Make(0.0f, 0.0f, 0.0f);	// initial assumption
																	//GLKVector3 last_pen_position = pen_position;
		GLKVector2 total_glyph_size = GLKVector2Make(0.0f, 0.0f);
		int gdata_index = 0;
		for(std::string::iterator it = string.begin(); it != string.end(); ++it){			
			const char ch = *it;
			FT_Error ret = FT_Load_Char(face, ch, FT_LOAD_RENDER);
			assert(ret == 0); //"Couldn't load char
			FT_GlyphSlot glyph_slot = face->glyph;
			gdata[gdata_index] = new GlyphData(ch, glyph_slot, pen_position);

			GLKVector2 eff_curr_glyph_size = gdata[gdata_index]->GetSize() +
			GLKVector2Make(gdata[gdata_index]->GetBearing().x, (gdata[gdata_index]->GetSize().y - gdata[gdata_index]->GetBearing().y));
			total_glyph_size.x += eff_curr_glyph_size.x;
			if(eff_curr_glyph_size.y > total_glyph_size.y){
				total_glyph_size.y = eff_curr_glyph_size.y;
			}
			he_Trace("%c\t%@\t%@\n",ch, eff_curr_glyph_size, total_glyph_size);
			// For some twisted Reason, FreeType measures font size in terms of 1/64ths of pixels.
			//Thus, to make a font advance for next char.. if looping
			//last_pen_position = pen_position;
			pen_position.x += (glyph_slot->advance.x >> 6);
			pen_position.y += (glyph_slot->advance.y >> 6);
			gdata_index++;
		}
		
		// Create glyphs
		pen_position = GLKVector3Make(-total_glyph_size.x/2.0f, 0.0f, 0.0f);	// final assumption
		gdata_index = 0;
		for(std::string::iterator it = string.begin(); it != string.end(); ++it){
			float trans_x = pen_position.x + gdata[gdata_index]->GetPenPosition().x + gdata[gdata_index]->GetSize().x/2.0f + gdata[gdata_index]->GetBearing().x;
			float trans_y = pen_position.y + gdata[gdata_index]->GetBearing().y/2.0f;
			GLKVector3 trans = GLKVector3Make(trans_x, trans_y, 0.0f);
			he_Trace("Pen: %@\ttrans: %@\n%@\n",pen_position,trans,*(gdata[gdata_index]));
			txt->MoveSubview(new Glyph(Frame(Transform_Create(trans), gdata[gdata_index]->GetSize()), gdata[gdata_index], shader.Get(), color));
			gdata_index++;
		}

		gdata_index = 0;
		for(std::string::iterator it = string.begin(); it != string.end(); ++it){
			delete gdata[gdata_index];
			gdata_index++;
		}
		delete [] gdata;
		return txt;
	}
}
///EOF
