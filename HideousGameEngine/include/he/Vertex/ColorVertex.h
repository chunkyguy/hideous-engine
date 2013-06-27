//
//  ColorVertex.h
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HEAssets__ColorVertex__
#define __HEAssets__ColorVertex__

#include <he/Vertex/IVertex.h>
#include <he/Vertex/VertexData.h>

namespace he{
	
	class ColorVertex : public IVertex{
	public:
		struct Data{
			GLKVector2 position;
			GLKVector4 color;
		};
		
		// As square of two colors
		ColorVertex(const Data &a, const Data &d);
		// As rect of 4 colors
		ColorVertex(const Data &a, const Data &b, const Data &c, const Data &d);
		
		/** Get Position data */
		const Vertex::V2 &GetVertexPositionData() const;
		
		/** Get Color data */
		const Vertex::V4 &GetVertexColorData() const;
		
	private:
		virtual const GLfloat *raw_data(const DataType dt) const;
		
		Vertex::V2 position_data_;	/**< The position data */
		Vertex::V4 color_data_;		/**< The color data */
	};
}

#endif /* defined(__HEAssets__ColorVertex__) */
