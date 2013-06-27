//
//  RenderObject.h
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
 
#ifndef __HEAssets__RenderObject__
#define __HEAssets__RenderObject__
#include <he/Utils/GLKMath_Additions.h>

namespace he{
	
	class IShader;
	class IVertex;
	class Texture;
	
	class RenderObject{
	public:
		RenderObject(const IVertex *vertex_data = 0,
					 const IShader *shader = 0,
					 const Texture *texture = 0,
					 const GLKMatrix4 mvp = GLKMatrix4Identity,
 					 const GLKVector4 color = GLKVector4Make(1.0,1.0,1.0,1.0));
		void Render() const;
		
		void SetVertexData(const IVertex *data);
		const IVertex *GetVertexData() const;

		void SetShader(const IShader *shader);
		const IShader *GetShader() const;
		
		void SetTexture(const Texture *texture);
		const Texture *GetTexture() const;

		void SetMVP(const GLKMatrix4 &mvp);
		const GLKMatrix4 GetMVP() const;

		void SetColor(const GLKVector4 &color);
		const GLKVector4 GetColor() const;
		
		const IVertex *vertex_data_;
		const IShader *shader_;
		const Texture *texture_;
		GLKMatrix4 mvp_;
		GLKVector4 color_;
	};
}
#endif /* defined(__HEAssets__RenderObject__) */
