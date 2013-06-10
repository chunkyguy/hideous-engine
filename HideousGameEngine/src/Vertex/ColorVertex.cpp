//
//  ColorVertex.cpp
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Vertex/ColorVertex.h>

#include <he/Utils/DebugHelper.h>
namespace he{
	
	ColorVertex::ColorVertex(float width, float height) :
	IVertex(4),
	position_data_()
	{
		GLKVector2 min = GLKVector2Make(-width/2, -height/2);
		GLKVector2 max = GLKVector2Make(width/2, height/2);
		Vertex::Set(position_data_, min, max);
		he_Trace("ColorVertex:\nmin = %@\nmax = %@\n",min, max);
		he_Trace("ColorVertex:\n%@\n",position_data_);
	}
	
	ColorVertex::ColorVertex(float x0, float y0, float x1, float y1) :
	IVertex(4),
	position_data_()
	{
		GLKVector2 min = GLKVector2Make(x0, y0);
		GLKVector2 max = GLKVector2Make(x1, y1);
		Vertex::Set(position_data_, min, max);
		he_Trace("ColorVertex:\n%@\n",position_data_);
	}
	
	const GLfloat *ColorVertex::GetPositionData() const{
		return &position_data_.data[0];
	}
	const GLfloat *ColorVertex::GetTextureData() const{
		return nullptr;
	}
	const Vertex::V2 &ColorVertex::GetVertexData() const{
		return position_data_;
	}

}
//EOF