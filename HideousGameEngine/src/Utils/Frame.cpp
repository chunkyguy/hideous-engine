//
//  Frame.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "Frame.h"

#include <he/Utils/DebugHelper.h>

namespace he{
	Frame::Frame(const Transform transform, const GLKVector2 size) :
	transform_(transform),
	size_(size)
	{
		GLKVector2 trans_pos = Transform_GetPosition(transform_);
		Vertex::Set(rect_, trans_pos-size_/2.0f, trans_pos+size_/2.0f);
		assert(size_ == (Vertex::GetVertex(rect_, Vertex::kD) - Vertex::GetVertex(rect_, Vertex::kA)));
	}
	
	GLKVector2 Frame::GetOrigin() const{
		return Vertex::GetVertex(rect_, Vertex::kA);
	}
	
	void Frame::SetOrigin(const GLKVector2 &origin){
		Vertex::Translate(rect_, origin);
		Transform_SetPosition(&transform_, origin - Transform_GetPosition(transform_));
	}
	
	GLKVector2 Frame::GetSize() const{
		return size_;
	}
	
	void Frame::SetSize(const GLKVector2 &size){
		Vertex::Scale(rect_, size - size_);
		size_ = size;
	}
	
	const Transform &Frame::GetTransform() const{
		return transform_;
	}
	Transform *Frame::GetTransformPtr(){
		return &transform_;
	}
	
	void Frame::SetTransform(const he::Transform &transform){
		Vertex::Translate(rect_, Transform_GetPosition(transform) - Transform_GetPosition(transform_));
		transform_ = transform;
	}
	
	Vertex::V2 Frame::GetRect() const{
		return rect_;
	}
	Vertex::V2 Frame::GetGlobalRect() const{
		Vertex::V2 world_frame(rect_);
		//	he_Trace("Frame::GetGlobalRect:BEF\n%@\n",world_frame);
		he::Vertex::ApplyTransform(world_frame, transform_);
		//	he_Trace("Frame::GetGlobalRect:AFT\n%@\n",world_frame);
		return world_frame;
		
	}
	void Frame::SetRect(const Vertex::V2 &rect){
		rect_ = rect;
		size_ = Vertex::GetVertex(rect_, Vertex::kD) - Vertex::GetVertex(rect_, Vertex::kA);
		Transform_SetPosition(&transform_, size_/2.0f);
	}
	
	std::ostream &operator<<(std::ostream &os, const Frame &frame){
		os << frame.GetRect();
		return os;
	}

	Frame CreateLocalFrame(const Frame &frame){
		return he::Frame(he::Transform_Create(GLKVector3Make(0, 0, 0)), frame.GetSize());
	}

}

///EOF
