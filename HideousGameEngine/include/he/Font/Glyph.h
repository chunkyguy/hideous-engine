//
//  Glyph.h
//  HideousGameEngine
//
//  Created by Sid on 23/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_Glyph_h
#define HideousGameEngine_Glyph_h
#include <string>

#include "ft2build.h"
#include FT_FREETYPE_H

#include <he/UI/View.h>
#include <he/Utils/GLKMath_Additions.h>
#include <he/Utils/Frame.h>

namespace he {
	class RenderObject;
	class TextShader;
	class Texture;
	class TextureVertex;
	
	class GlyphData{
	public:
		struct Size{
			Size(int width, int height) : w(width), h(height)
			{}
			
			int w; int h;
		};

		GlyphData(char charctr, FT_GlyphSlot &glyph_slot, GLKVector3 pen_pos);
		~GlyphData();

		char GetChar() const;
		GLubyte *GetTexData() const;
		GLKVector2 GetTexSize() const;
		GLKVector2 GetSize() const;
		GLKVector2 GetBearing() const;
		GLKVector3 GetPenPosition() const;

	private:
		char ch;
		GLubyte *tex_data;
		Size tex_size;
		Size size;
		Size bearing;
		GLKVector3 pen_pos;
	};

	std::ostream &operator<<(std::ostream &os, const GlyphData::Size &sz);
	std::ostream &operator<<(std::ostream &os, const GlyphData &gd);

	
	class Glyph : public View{
	public:
		Glyph(Frame frame, GlyphData *data, TextShader *shader, GLKVector4 color);
		virtual ~Glyph();
		
	protected:
		void update(float dt);
		void render();
		
	private:
		RenderObject *render_object_;
		Texture *texture_;
		TextureVertex *vertex_data_;
	};
}


#endif
