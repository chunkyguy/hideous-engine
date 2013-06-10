//
//  TextureVertex.h
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HEAssets__TextureVertex__
#define __HEAssets__TextureVertex__
#include <he/Utils/GLKMath_Additions.h>

#include <he/Vertex/IVertex.h>
#include <he/Vertex/VertexData.h>

namespace he{
	class TextureAtlasRegion;
	
	class TextureVertex : public IVertex{
	public:
		
		const GLfloat *GetRawData(const IVertex::DataType dt) const;
		
		// Create vertex data. Aspect lock is applicable for disproportioned texCoords not posCoords
		TextureVertex(float width, float height,
				  bool aspect_lock = true, GLKVector4 texture_coords = GLKVector4Make(0, 0, 1, 1));
		
		TextureVertex(const Vertex::V2 &position_data, const Vertex::V2 &texture_data);
		
		// if width / height are not provided, pick the size from atlas data.
		TextureVertex(const TextureAtlasRegion *region, float width = -1, float height = -1, const bool aspect_lock = true);
		
		const Vertex::V2 &GetVertexPositionData() const;
		const Vertex::V2 &GetVertexTextureData() const;

	private:
		void set_data(const GLKVector4 &pos_coords, const GLKVector4 &tex_coords, const bool aspect_lock);
		void apply_aspect_correctnes(const GLKVector4 &texture_coords);
		
		Vertex::V2 position_data_;
		Vertex::V2 texture_data_;
	};
}
#endif /* defined(__HEAssets__TextureVertex__) */
