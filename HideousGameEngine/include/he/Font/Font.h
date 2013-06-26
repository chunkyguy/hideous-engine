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

#include <he/Utils/Frame.h>

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

	/** Font class */
	class Font{
	public:
		/** Creates a font 
		 @param name The name of the font. Can be of type ttf, or whatever supported by Freetype.
		 @param size The size of the font.
		 */
		Font(std::string font_path, unsigned int size);
		~Font();
		const FT_Face &GetFace() const;
		
	private:
		FT_Face face_;
	};
	
	class FontLibrary{
	public:
		FontLibrary();
		~FontLibrary();
		
		FT_Library library_;
	};
	extern FontLibrary *g_FontLib;
}
#endif /* defined(__HEAssets__Font__) */
