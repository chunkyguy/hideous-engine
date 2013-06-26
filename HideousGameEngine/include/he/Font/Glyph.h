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

#include <he/Utils/GLKMath_Additions.h>
#include <he/Utils/Frame.h>

namespace he {
	class RenderObject;
	class TextShader;
	class Texture;
	class TextureVertex;
	
	class Glyph{
	public:
		Glyph(std::string glyph_name, FT_GlyphSlot &glyph, GLKVector2 penPosition, TextShader *shader, GLKVector4 color);
		~Glyph();
		
		Frame frame_;
		RenderObject *render_object_;
		GLKVector2 size_;
		
	private:
		Texture *texture_;
		TextureVertex *vertex_data_;
	};
}


#endif
