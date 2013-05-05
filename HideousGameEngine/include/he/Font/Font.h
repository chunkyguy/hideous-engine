//
//  Font.h
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HEAssets__Font__
#define __HEAssets__Font__
#include <string>
#include <list>
#include <GLKit/GLKMath.h>
#include <OpenGLES/ES2/gl.h>
#include "ft2build.h"
#include FT_FREETYPE_H

//	Instructions to add libFreetype2
/*
 1a. Copy 'libFreetype2.a' from to the Project directory
 1a-a. Add libFreetype2.a to Xcode from Project directory.
 "/Volumes/DrivePlusPlus/Languages/std_lib/freetype_2_ios/libFreetype2.a"
 Skip to 2b
 
 1b. Add 'libFreetype2.a' from following path to Xcode:
 "/Volumes/DrivePlusPlus/Languages/std_lib/freetype_2_ios/libFreetype2.a"
 
 2. Go to Build Settings > Search Paths >
 2a. Add to Library Search Path:
 "/Volumes/DrivePlusPlus/Languages/std_lib/freetype_2_ios/"
 
 2b. Add to User Header Search Path:
 "/Volumes/DrivePlusPlus/Languages/std_lib/freetype_2_ios/include/freetype2"
 
 3. Select Always Search User Paths to YES.
 */


namespace he{
	
	class RenderObject;
	class VertexTex;
	class Texture;
	class RectTextSh;
	
	class GlyphData{
	public:
		GlyphData(std::string font_name, std::string char_name, FT_GlyphSlot &glyph, GLKVector2 penPosition,	RectTextSh *shader, GLKVector4 color);
		~GlyphData();
		
		GLKVector2 position_;
		RenderObject *render_object_;
		GLKVector2 size_;
	private:
		Texture *texture_;
		VertexTex *vertex_data_;
	};
	
	
	class Font{
	public:
		Font(std::string name, unsigned int size, GLKVector4 color);
		~Font();
		void LoadGlyph(std::string text, GLKVector2 penPosition = GLKVector2Make(0,0));
		void UnloadGlyph();
		std::list<GlyphData *> &GetGlyph();
		
		GLKVector4 color_;
	private:
		class Library{
		public:
			Library();
			~Library();

			FT_Library object_;
		};
		Library *GetLibrary();
		static void CleanLibrary();

		std::string name_;
		FT_Face face_;
		int glyph_count_;
		std::list<GlyphData *>glyph_data_;
		RectTextSh *shader_;
		static Library *library_;
	};
}
#endif /* defined(__HEAssets__Font__) */
