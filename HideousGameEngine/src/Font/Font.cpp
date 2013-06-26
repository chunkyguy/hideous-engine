//
//  Font.cpp
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Font/Font.h>

#include <he/Utils/DebugHelper.h>

namespace he{
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Font
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	Font::Font(std::string font_path, unsigned int size)
	{
		he_Trace("loading font: %@\n", font_path);
		
		FT_Error error = FT_New_Face(g_FontLib->library_, font_path.c_str(), 0, &face_);
		assert(error != FT_Err_Unknown_File_Format);		//"Font format not supported"
		assert(!error); // "Unable to open font"
		FT_Set_Pixel_Sizes(face_, 0, size);
	}

	Font::~Font(){
		FT_Done_Face(face_);
	}

	const FT_Face &Font::GetFace() const{
		return face_;
	}

	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: FontLibrary
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	FontLibrary *g_FontLib = nullptr;

	FontLibrary::FontLibrary(){
		FT_Error error = FT_Init_FreeType(&library_);
		assert(!error);
	}
	FontLibrary::~FontLibrary(){
		FT_Done_FreeType(library_);
	}
}