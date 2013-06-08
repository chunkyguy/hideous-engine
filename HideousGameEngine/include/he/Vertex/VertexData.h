//
//  VertexData.h
//  HEAssets
//
//  Created by Sid on 22/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HEAssets__VertexData__
#define __HEAssets__VertexData__

#include<ostream>

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
		
		// Create with raw data. Requires a pointer to array 8 floats
		explicit VertexData(const GLfloat *data);
		
		// Create with a perfectly aligned rectangles, using endpoints A and D
		VertexData(const GLfloat a_x, const GLfloat a_y, const GLfloat d_x, const GLfloat d_y);

		// Create with a perfectly aligned rectangles, using endpoints A and D
		VertexData(const GLKVector2 &a, const GLKVector2 &d);

		// Create with a perfectly aligned rectangles, using endpoints A and D
		// a_d = {a.x, a.y, d.x, d.y}
		VertexData(const GLKVector4 &a_d);

		// Create with 4 endpoints. Use for cases like skewed / rotated rectangles
		VertexData(const GLKVector2 &a, const GLKVector2 &b, const GLKVector2 &c, const GLKVector2 &d);

		// Test whether the point is inside the rectangle
		bool Contains(const GLfloat x, const GLfloat y) const;

		// Test whether the point is inside the rectangle
		bool Contains(const GLKVector2 &point) const;
		
		// Test whether the other rectangle is totally inside the rectangle
		bool Contains(const VertexData &other) const;
		
		// Returns the pointer to allocated data. Used for GL
		const GLfloat *GetData() const;

		// Returns the size of data. Used for passing to GL
		const GLsizei GetSize() const;
		
		// Translate each point
		void Translate(const GLfloat x, const GLfloat y);
		void Translate(const GLKVector2 &point);
		
		// Scale each point
		void Scale(const GLfloat x, const GLfloat y);
		void Scale(const GLKVector2 &value);

		// Set individual vertex index
		void SetVertex(const VertexIndex index, const GLKVector2 &value);
		
		// Get point at individual index
		const GLKVector2 GetVertex(const VertexIndex index) const;
		
	private:
		// Load the data. Must be a pointer to array of 8 floats
		void load(const GLfloat *data);
		
		enum{Ax = 0, Ay = 1, Bx = 2, By = 3, Cx = 4, Cy = 5, Dx = 6, Dy = 7};
		GLfloat data_[8];	//num_vertices * coord_per_vertex  = 4 * 2
	};
	
	std::ostream &operator<<(std::ostream &os, const VertexData &data);
}
#endif /* defined(__HEAssets__VertexData__) */
