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

	ColorVertex::ColorVertex(const Data &a, const Data &b, const Data &c, const Data &d) :
	IVertex(4),
	color_data_(),
	position_data_()
	{
		Vertex::Set(position_data_, a.position, b.position, c.position, d.position);
		Vertex::Set(color_data_, a.color, a.color, d.color, d.color);
	}

	ColorVertex::ColorVertex(const Data &a, const Data &d) :
	IVertex(4),
	color_data_(),
	position_data_()
	{
		Vertex::Set(position_data_, a.position, d.position);
		he_Trace("position: \n%@\n",position_data_);

		he_Trace("filing color:\n %@\n",a.color);
		Vertex::Set(color_data_, a.color, a.color, d.color, d.color);
		he_Trace("color: \n%@\n",color_data_);
	}
	
	const GLfloat *ColorVertex::GetRawData(const DataType dt) const{
		switch(dt){
			case IVertex::kPosition:
				return &position_data_.data[0]; break;
				
			case IVertex::kColor:
				return &color_data_.data[0]; break;
				
			case IVertex::kTexture:
				return nullptr;
		}
		return nullptr;
	}
	const Vertex::V2 &ColorVertex::GetVertexData() const{
		return position_data_;
	}
	const Vertex::V4 &ColorVertex::GetColorData() const{
		return color_data_;
	}

}
//EOF