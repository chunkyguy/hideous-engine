//
//  Frame.h
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_Frame_h
#define HideousGameEngine_Frame_h
#include <he/Utils/Transform.h>
#include <he/Utils/GLKMath_Additions.h>
#include <he/Vertex/VertexData.h>
namespace he {
	
	class Frame{
	public:
		Frame(const Transform transform, const GLKVector2 size = GLKVector2Make(0,0));

		GLKVector2 GetOrigin() const;
		void SetOrigin(const GLKVector2 &origin);
		
		GLKVector2 GetSize() const;
		void SetSize(const GLKVector2 &size);

		const Transform &GetTransform() const;
		Transform *GetTransformPtr();
		void SetTransform(const Transform &transform);
		
		Vertex::V2 GetRect() const;
		
		/** The frame in world space.
		 Basically just GetFrame() * GetMV() 
		 */
		Vertex::V2 GetGlobalRect() const;
		
		void SetRect(const Vertex::V2 &rect);

	private:
		void update_values();
		
		GLKVector2 size_;
		Vertex::V2 rect_;
		Transform transform_;
	};

	std::ostream &operator<<(std::ostream &os, const Frame &frame);

}//ns he


#endif
