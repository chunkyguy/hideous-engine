//
//  VertexCol.cpp
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Vertex/VertexCol.h>
namespace he{
	
	VertexCol::VertexCol(double width, double height) :
	position_data_(VertexData(-width/2, -height/2, width/2, height/2))
	{	}
	
	VertexCol::VertexCol(double x0, double y0, double x1, double y1) :
	position_data_(VertexData(x0, y0, x1, y1))
	{	}
}
//EOF