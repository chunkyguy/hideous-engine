//
//  RenderObject.h
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
 
#ifndef __HEAssets__RenderObject__
#define __HEAssets__RenderObject__
#include <GLKit/GLKMath.h>

namespace he{
	
	class IShader;
	class IVertex;
	class Texture;
	
	class RenderObject{
	public:
		RenderObject(IVertex *vertex_data = 0,
					 IShader *shader = 0,
					 Texture *texture = 0,
					 GLKMatrix4 mvp = GLKMatrix4Identity,
 					 GLKVector4 color = GLKVector4Make(1.0,1.0,1.0,1.0));
		void Render();

		GLKVector4 color_;
		GLKMatrix4 mvp_;
		IShader *shader_;
		Texture *texture_;
		IVertex *vertex_data_;
	};
}
#endif /* defined(__HEAssets__RenderObject__) */
