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
		
		const GLfloat *GetRawData(const IVertex::DataType dt) const;

		// As square of two colors
		ColorVertex(const Data &a, const Data &d);
		// As rect of 4 colors
		ColorVertex(const Data &a, const Data &b, const Data &c, const Data &d);
		const Vertex::V2 &GetVertexData() const;
		const Vertex::V4 &GetColorData() const;
		
	private:
		Vertex::V2 position_data_;
		Vertex::V4 color_data_;
	};
}

#endif /* defined(__HEAssets__ColorVertex__) */
