//
//  IVertex.h
//  HEAssets
//
//  Created by Sid on 26/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HEAssets_IVertex_h
#define HEAssets_IVertex_h
#include <OpenGLES/ES2/gl.h>

namespace he{
	class IVertex{
	public:
		enum DataType {kPosition, kTexture, kColor};

		IVertex(GLint count = 4) : count_(count){}
		
		virtual ~IVertex(){}
		
		const GLfloat *GetRawData(const DataType dt) const{
			return raw_data(dt);
		};
		
		const GLint GetCount() const{
			return count_;
		}
		
		void SetCount(GLint count){
			count_ = count;
		}
		
	private:
		
		virtual const GLfloat *raw_data(const DataType dt) const = 0;
		
		GLint count_;
	};
}
#endif
