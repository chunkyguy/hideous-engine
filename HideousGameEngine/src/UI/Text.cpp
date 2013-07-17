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
	TextView::TextView(const Transform &transform) :
	View(transform),
	size_(GLKVector2Make(0.0f, 0.0f))
	{}
	
	void TextView::Update(float dt) {
		View::Update(dt);
	}
	
	void TextView::Render() {
		View::Render();
	}

	GLKVector2 TextView::GetSize() const {
		return size_;
	}
	
	void TextView::SetSize(const GLKVector2 &size) {
		size_ = size;
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: TextFactory
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TextViewFactory::TextViewFactory(TextShader *shader, Font *font_m) {
		font_m_.Move(font_m);
		shader_.Set(shader);
	}

	TextView *TextViewFactory::CreateTextView(const Transform &transform, const std::string &string, GLKVector4 color){
		TextView *txt = new TextView(transform);
		
		const FT_Face face = font_m_.Get()->GetFace();
		GlyphData **gdata = new GlyphData* [string.size()];
		// create textures
		GLKVector3 pen_position = GLKVector3Make(0.0f, 0.0f, 0.0f);	// initial assumption
																	//GLKVector3 last_pen_position = pen_position;
		GLKVector2 total_glyph_size = GLKVector2Make(0.0f, 0.0f);
		int gdata_index = 0;
		for(std::string::const_iterator it = string.begin(); it != string.end(); ++it){
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
		txt->SetSize(total_glyph_size);
		
		// Create glyphs
		pen_position = GLKVector3Make(-total_glyph_size.x/2.0f, 0.0f, 0.0f);	// final assumption
		gdata_index = 0;
		for(std::string::const_iterator it = string.begin(); it != string.end(); ++it){
			float trans_x = pen_position.x + gdata[gdata_index]->GetPenPosition().x + gdata[gdata_index]->GetBearing().x + gdata[gdata_index]->GetSize().x/2.0f ;
			float trans_y = pen_position.y + gdata[gdata_index]->GetPenPosition().y + gdata[gdata_index]->GetBearing().y/2.0f;
			GLKVector3 trans = GLKVector3Make(trans_x, trans_y, 0.0f);
			he_Trace("Pen: %@\ttrans: %@\n%@\n",pen_position,trans,*(gdata[gdata_index]));
			txt->MoveSubview(new Glyph(Frame(Transform_Create(trans), gdata[gdata_index]->GetSize()), gdata[gdata_index], shader_.Get(), color));
			gdata_index++;
		}

		gdata_index = 0;
		for(std::string::const_iterator it = string.begin(); it != string.end(); ++it){
			delete gdata[gdata_index];
			gdata_index++;
		}
		delete [] gdata;
		return txt;
	}
}
///EOF
