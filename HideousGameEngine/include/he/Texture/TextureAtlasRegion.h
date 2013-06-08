//
//  TextureAtlasRegion.h
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_TextureAtlasRegion_h
#define HideousGameEngine_TextureAtlasRegion_h
#include <string>

#include <he/Utils/GLKMath_Additions.h>

namespace he {
	class TextureAtlasRegion{
	public:
		// Long version: tex-coords are calculated.
		TextureAtlasRegion(
						   /*mandatory*/
						   const std::string &name,
						   const GLKVector4 &texture_rect,
   						   const GLKVector2 &total_texture_size,
						   /*optional*/
						   const GLKVector2 &sprite_offset,
						   const GLKVector2 &sprite_size,
						   const bool sprite_trimmed,
						   const bool texture_rotated,
						   /*derivable from other data*/
						   const GLKVector4 &sprite_color_rect,
						   const GLKVector2 &sprite_source_size);

		// Short version: data gets autofilled. tex-coords are calculated.
		TextureAtlasRegion(
						   /*mandatory*/
						   const std::string &name,
						   const GLKVector4 &texture_rect,
   						   const GLKVector2 &total_texture_size,
						   /*optional*/
						   const GLKVector2 &sprite_offset = GLKVector2Make(0, 0),
						   const GLKVector2 &sprite_size = GLKVector2Make(0, 0),
						   const bool sprite_trimmed = false,
						   const bool texture_rotated = false);


		/*mandatory*/
		const std::string name_;
		const GLKVector4 texture_rect_;
		const GLKVector2 total_texture_size_;
		/*optional*/
		const GLKVector2 sprite_offset_;
		const GLKVector2 sprite_size_;
		const bool sprite_trimmed_;
		const bool texture_rotated_;
		/*derivable from other data*/
		const GLKVector4 sprite_color_rect_;
		const GLKVector2 sprite_source_size_;
		GLKVector4 tex_coords_;
		
	private:
		void calc_tex_coords();
	};
}

#endif
