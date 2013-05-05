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
#include <he/Vertex/IVertex.h>

namespace he{

	class VertexParData{
	public:
		VertexParData(int count);
		~VertexParData();
		GLfloat *GetData();
		GLsizei GetSize();
		
	private:
		GLfloat *data_;
		GLsizei size_;
	};
	
	class VertexPar : public IVertex{
	public:
		VertexPar(int count, double point_size = 15.0);
		
		VertexParData position_data_;
		int count_;
		double point_size_;
	};
}
#endif /* defined(__HEAssets__VertexPar__) */
