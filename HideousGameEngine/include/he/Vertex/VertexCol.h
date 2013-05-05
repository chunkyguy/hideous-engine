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
		VertexCol(double width, double height);
		VertexCol(double x0, double y0, double x1, double y1);
		
		VertexData position_data_;
	};
}

#endif /* defined(__HEAssets__VertexCol__) */
