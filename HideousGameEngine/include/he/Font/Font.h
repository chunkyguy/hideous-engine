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
#include <he/Utils/GLKMath_Additions.h>
#include <OpenGLES/ES2/gl.h>
#include "ft2build.h"
#include FT_FREETYPE_H

#include <he/Utils/Transform.h>

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
	class TextureVertex;
	class Texture;
	class TextShader;
	
	class Text{
	public:
		class Glyph{
		public:
			Glyph(std::string font_name, std::string char_name, FT_GlyphSlot &glyph, GLKVector2 penPosition,	TextShader *shader, GLKVector4 color);
			~Glyph();
			
			Transform transform_;
			RenderObject *render_object_;
			GLKVector2 size_;
		private:
			Texture *texture_;
			TextureVertex *vertex_data_;
		};

		Text(std::string string = "", Transform transform = Transform(), GLKVector4 color = GLKVector4Make(0,0,0,1));
		~Text();
		void Render();
		void SetTransform(Transform transform);
		const Transform &GetTransform() const;
		GLKVector2 GetSize();
		
		Glyph ** data_;
		std::string string_;
		Transform transform_;
		GLKVector4 color_;
	};
	
	class Font{
	public:
		Font(std::string name, unsigned int size);
		~Font();
		void LoadText(Text *text);
		
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
		TextShader *shader_;
		static Library *library_;
	};
}
#endif /* defined(__HEAssets__Font__) */
