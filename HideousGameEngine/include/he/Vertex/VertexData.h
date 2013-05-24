//
//  VertexData.h
//  HEAssets
//
//  Created by Sid on 22/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HEAssets__VertexData__
#define __HEAssets__VertexData__
#include <OpenGLES/ES2/gl.h>
#include <he/Utils/GLKMath_Additions.h>

namespace he{
	//bottom-left, top-right
	//	Visual:
	//    C----------D
	//    |			|
	//    |			|
	//    |			|
	//    |			|
	//	 A-----------B

	class VertexData{
	public:
		typedef enum{kA, kB, kC, kD} VertexIndex;
		
		VertexData();
		explicit VertexData(GLfloat *data);
		// for perfect squares, using endpoints A and D
		VertexData(GLfloat a_x, GLfloat a_y, GLfloat d_x, GLfloat d_y);
		// for skewed / rotated squares
		VertexData(GLKVector2 a, GLKVector2 b, GLKVector2 c, GLKVector2 d);
		VertexData(const VertexData &other);
		bool Contains(GLfloat x, GLfloat y);
		GLfloat *GetData();
		GLsizei GetSize();
		void Scale(GLfloat x, GLfloat y);
		void operator=(const VertexData &other);
		void SetVertex(VertexIndex index, GLKVector2 value);
		GLKVector2 GetVertex(VertexIndex index);
		
	private:
		enum{Ax = 0, Ay = 1, Bx = 2, By = 3, Cx = 4, Cy = 5, Dx = 6, Dy = 7};
		GLfloat data_[8];	//num_vertices * coord_per_vertex  = 4 * 2
	};
}
#endif /* defined(__HEAssets__VertexData__) */
