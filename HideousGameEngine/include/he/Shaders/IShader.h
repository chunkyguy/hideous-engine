//
//  IShader.h
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
 
#ifndef HEAssets_IShader_h
#define HEAssets_IShader_h

namespace he{
	class RenderObject;
	
	class IShader{
	public:
		virtual ~IShader(){}
		void Render(const RenderObject *ro) const{
			render(ro);
		}
		
	private:
		virtual void render(const RenderObject *ro) const = 0;
	};
}
#endif
