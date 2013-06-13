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
		Vertex::Set(rect_, transform_.GetPosition()-size_/2.0f, transform_.GetPosition()+size_/2.0f);
		he_Trace("Frame: pos = %@\n size = %@\nrect = %@\n",transform.GetPosition(),size,rect_);

		assert(size_ == (Vertex::GetVertex(rect_, Vertex::kD) - Vertex::GetVertex(rect_, Vertex::kA)));
	}
	
	GLKVector2 Frame::GetOrigin() const{
		return Vertex::GetVertex(rect_, Vertex::kA);
	}
	
	void Frame::SetOrigin(const GLKVector2 &origin){
		Vertex::Translate(rect_, origin);
		transform_.SetPosition(origin - transform_.GetPosition());
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
	
	void Frame::SetTransform(const he::Transform &transform){
		Vertex::Translate(rect_, transform.GetPosition() - transform_.GetPosition());
		transform_ = transform;
	}
	
	Vertex::V2 Frame::GetRect() const{
		return rect_;
	}
	
	void Frame::SetRect(const Vertex::V2 &rect){
		rect_ = rect;
		size_ = Vertex::GetVertex(rect_, Vertex::kD) - Vertex::GetVertex(rect_, Vertex::kA);
		transform_.SetPosition(size_/2.0f);
	}
}

///EOF
