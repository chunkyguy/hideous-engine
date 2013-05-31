//
//  VertexPar.h
//  HEAssets
//
//  Created by Sid on 29/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HEAssets__VertexPar__
#define __HEAssets__VertexPar__

#include <OpenGLES/ES2/gl.h>

#include <he/Utils/GLKMath_Additions.h>
#include <he/Vertex/IVertex.h>

namespace he{
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: VertexPar
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	class VertexPar : public IVertex{
	public:
		const GLfloat *GetPositionData() const;

		~VertexPar();
		VertexPar(int count, double point_size = 15.0);
		void SetData(int index, const GLKVector2 &data);
		GLfloat GetPointSize() const;
		GLsizei GetSize() const;

	private:
		GLfloat *data_;
		GLsizei size_;
		double point_size_;
	};
}
#endif /* defined(__HEAssets__VertexPar__) */
