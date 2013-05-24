//
//  VertexTex.h
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HEAssets__VertexTex__
#define __HEAssets__VertexTex__
#include <he/Utils/GLKMath_Additions.h>

#include <he/Vertex/IVertex.h>
#include <he/Vertex/VertexData.h>

namespace he{
	class VertexTex : public IVertex{
	public:
		// Create vertex data. Aspect lock is applicable for disproportioned texCoords not posCoords
		VertexTex(double width, double height,
				  bool aspect_lock = true, GLKVector4 texture_coords = GLKVector4Make(0, 0, 1, 1));

		VertexData position_data_;
		VertexData texture_data_;
	};
}
#endif /* defined(__HEAssets__VertexTex__) */
