//
//  VertexTex.cpp
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Vertex/VertexTex.h>

namespace he{
	VertexTex::VertexTex(double width, double height, bool aspect_lock, GLKVector4 texture_coords) :
	position_data_(VertexData(-width/2.0, -height/2.0, width/2.0, height/2.0)),
	texture_data_(texture_coords.x, texture_coords.y, texture_coords.z, texture_coords.w)
	{
		if(aspect_lock){
			double eff_w = texture_coords.z - texture_coords.x;
			double eff_h = texture_coords.w - texture_coords.y;
			double aspect_ratio;
			if(eff_w < eff_h){
				aspect_ratio = eff_w/eff_h;
				position_data_.Scale(aspect_ratio, 1.0);
			}else if(eff_h < eff_w){
				aspect_ratio = eff_h/eff_w;
				position_data_.Scale(1.0, aspect_ratio);
			}
		}
	}
}