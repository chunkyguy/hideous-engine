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

	/** VertexData for a texture.
		Possible use is while generating vertex-data from an TextureAtlas, or directly by providing texture coordinates.
	 */
	class TextureVertex : public IVertex{
	public:
		
		/** Create vertex data for explicitly provided values.
		 @param size The height width of the texture
		 @param aspect_lock Aspect lock is applicable for disproportioned texCoords not posCoords
		 @param texture_coords The texture coordinates. By default {0,0,1,1}
		 */
		TextureVertex(const GLKVector2 &size, const bool aspect_lock = true, const GLKVector4 texture_coords = GLKVector4Make(0, 0, 1, 1));
		
		/** Create Vertex data from position and texture data 
			@param position_data The position data.
			@param texture_data	The texture data.
		 */
		TextureVertex(const Vertex::V2 &position_data, const Vertex::V2 &texture_data);
		
		/** Create Vertex data from a TextureAtlas.
		@param region The region as calculated from a TextureAtlas.
		 @param aspect_lock Turn on lock to explicitly provide the width and height.
		 @param size If not provided, picked from the size from atlas data.
		 */
		TextureVertex(const TextureAtlasRegion &region, const bool aspect_lock = false, GLKVector2 size = GLKVector2Make(-1, -1));

		/** Get Vertex data */
		const Vertex::V2 &GetVertexPositionData() const;
		
		/** Get Texture data */
		const Vertex::V2 &GetVertexTextureData() const;

	private:
		/** Returns raw data.
		 Expected to be used in a shader.
		 Impl the virtual method of IVertex
		 */
		virtual const GLfloat *raw_data(const DataType dt) const;

		/** Common method to set create vertex datas from position and texture coords */
		void set_data(const GLKVector4 &pos_coords, const GLKVector4 &tex_coords, const bool aspect_lock);
		
		/**  Apply aspect correctness width wise, if required */
		void apply_aspect_correctnes(const GLKVector4 &texture_coords);
		
		Vertex::V2 position_data_;	/**< The position data */
		Vertex::V2 texture_data_;	/**< The texture data */
	};
}
#endif /* defined(__HEAssets__TextureVertex__) */
