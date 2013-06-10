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
		
		const GLfloat *GetPositionData() const;
		const GLfloat *GetTextureData() const;

		ColorVertex(float width, float height);
		ColorVertex(float x0, float y0, float x1, float y1);
		const Vertex::V2 &GetVertexData() const;
		
	private:
		Vertex::V2 position_data_;
	};
}

#endif /* defined(__HEAssets__ColorVertex__) */
