//
//  VertexCol.h
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HEAssets__VertexCol__
#define __HEAssets__VertexCol__

#include <he/Vertex/IVertex.h>
#include <he/Vertex/VertexData.h>

namespace he{
	class VertexCol : public IVertex{
	public:
		
		const GLfloat *GetPositionData() const;
		const GLfloat *GetTextureData() const;

		VertexCol(float width, float height);
		VertexCol(float x0, float y0, float x1, float y1);
		const VertexData &GetVertexData() const;
		
	private:
		VertexData position_data_;
	};
}

#endif /* defined(__HEAssets__VertexCol__) */
