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
#include <he/Utils/DebugHelper.h>

namespace he{
	
	namespace Vertex {
		//bottom-left, top-right
		//	Visual:
		//    C----------D
		//    |			|
		//    |			|
		//    |			|
		//    |			|
		//	 A-----------B
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// MARK: Types
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		typedef int Index;
		const int kA = 0;
		const int kB = 1;
		const int kC = 2;
		const int kD = 3;
		
		// 2 floats per vertex
		struct V2{
			V2(){
				bzero(static_cast<GLfloat *>(data), sizeof(data));
			}
			
			GLfloat data[8];
			static int vertex_count;
		};
		
		// 3 floats per vertex
		struct V3{
			V3(){
				bzero(static_cast<GLfloat *>(data), sizeof(data));
			}

			GLfloat data[12];
			static int vertex_count;
		};
		
		// 4 float per vertex
		struct V4{
			V4(){
				bzero(static_cast<GLfloat *>(data), sizeof(data));
			}

			GLfloat data[16];
			static int vertex_count;
		};
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// MARK: Set
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Create with raw data. Requires a pointer to array vertex_count floats
		template<typename V>
		void Set(V &slf, const GLfloat *data, int start = 0, int end = V::vertex_count * 4){
			assert(start >= 0);
			assert(end <= V::vertex_count * 4);
			for(int i = start; i < end; ++i){
				slf.data[i] = data[i];
				he_Trace("Set data[%d]=%f\n",i,slf.data[i]);
			}
		}
		
		// Create with raw data at a given index
		template<typename V>
		void Set(V &slf, const GLfloat *data, Index vi){
			int start = vi * V::vertex_count;
			int end = start + V::vertex_count;
			Set(slf, data, start, end);
		}
		
		// Set individual vertex index
		template<typename V, typename GLKVector>
		void Set(V &slf, const GLKVector &vec, Index vi){
			int start = vi * V::vertex_count;
			int end = start + V::vertex_count;
			Set(slf, vec.v, start, end);
		}
		
		// Create with 4 endpoints. Use for cases like skewed / rotated rectangles
		template <typename V, typename GLKVector>
		void Set(V &slf, const GLKVector &a, const GLKVector &b, const GLKVector &c, const GLKVector &d){
			Set(slf, a, kA);
			Set(slf, b, kB);
			Set(slf, c, kC);
			Set(slf, d, kD);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// MARK: Get
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Get point at individual index
		GLKVector2 GetVertex(const V2 &v, const Index vi);
		GLKVector3 GetVertex(const V3 &v, const Index vi);
		GLKVector4 GetVertex(const V4 &v, const Index vi);

		// Returns the size of data. Used for passing to GL
		template <typename V>
		const GLsizei GetSize(const V &slf){
			return sizeof(slf.data);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// MARK: Modify
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Translate each point
		template <typename V, typename GLKVector>
		void Translate(V &slf, const GLKVector &point){
			int j = 0;
			for(int i = 0; i < 4; ++i){
				for(int k = 0; k < V::vertex_count; ++k){
					slf.data[j++] += point.v[k];
				}
			}
		}
		
		// Scale each point
		template<typename V, typename GLKVector>
		void Scale(V &slf, const GLKVector &value){
			int j = 0;
			for(int i = 0; i < 4; ++i){
				for(int k = 0; k < V::vertex_count; ++k){
					slf.data[j++] *= value.v[k];
				}
			}
		}
		
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// MARK: Modify
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		std::ostream &operator<<(std::ostream &os, const V2 &slf);
		

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// MARK: Vertex2 overload
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Create with a perfectly aligned rectangles, using endpoints A and D
		void Set(V2 &slf, const GLKVector2 &a, const GLKVector2 &d);
		
		// Test whether the point is inside the rectangle
		bool Contains(const V2 &v, const GLKVector2 &point);
		
		// Test whether the other rectangle is totally inside the rectangle
		bool Contains(const V2 &slf, const V2 &other);
		
		
	}	/*namespace Vertex*/
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
	 class VertexData2{
	 public:
	 
	 VertexData2();
	 
	 // Create with raw data. Requires a pointer to array 8 floats
	 explicit VertexData2(const GLfloat *data);
	 
	 // Create with a perfectly aligned rectangles, using endpoints A and D
	 VertexData2(const GLfloat a_x, const GLfloat a_y, const GLfloat d_x, const GLfloat d_y);
	 
	 // Create with a perfectly aligned rectangles, using endpoints A and D
	 VertexData2(const GLKVector2 &a, const GLKVector2 &d);
	 
	 // Create with a perfectly aligned rectangles, using endpoints A and D
	 // a_d = {a.x, a.y, d.x, d.y}
	 VertexData2(const GLKVector4 &a_d);
	 
	 // Create with 4 endpoints. Use for cases like skewed / rotated rectangles
	 VertexData2(const GLKVector2 &a, const GLKVector2 &b, const GLKVector2 &c, const GLKVector2 &d);
	 
	 // Test whether the point is inside the rectangle
	 bool Contains(const GLfloat x, const GLfloat y) const;
	 
	 // Test whether the point is inside the rectangle
	 bool Contains(const GLKVector2 &point) const;
	 
	 // Test whether the other rectangle is totally inside the rectangle
	 bool Contains(const VertexData2 &other) const;
	 
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
	 
	 std::ostream &operator<<(std::ostream &os, const VertexData2 &data);
	 */
}
#endif /* defined(__HEAssets__VertexData__) */
