//
//  Transform.cpp
//  HideousGameEngine
//
//  Created by Sid on 06/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/Transform.h>

namespace he{
	Transform::Transform(GLKVector2 position, double rotation, GLKVector2 scale) :
	position_(position),
	rotation_(rotation),
	scale_(scale)
	{}
	
	GLKMatrix4 Transform::GetMV(){
		GLKMatrix4 tMat = GLKMatrix4MakeTranslation(position_.x, position_.y, -0.1);
		GLKMatrix4 rMat = GLKMatrix4MakeRotation(rotation_, 0.0, 0.0, 1.0);
		GLKMatrix4 sMat = GLKMatrix4MakeScale(scale_.x, scale_.y, 1.0);
		return GLKMatrix4Multiply(GLKMatrix4Multiply(tMat, rMat), sMat);
	}
	
	const double Transform::GetRotation() const{
		return rotation_;
	}
	void Transform::SetRotation(const double rotation){
		rotation_ = rotation;
	}
	
	const GLKVector2 &Transform::GetPosition() const{
		return position_;
	}
	void Transform::SetPosition(const GLKVector2 &position){
		position_ = position;
	}
	
	const GLKVector2 &Transform::GetScale() const{
		return scale_;
	}
	void Transform::SetScale(const GLKVector2 &scale){
		scale_ = scale;
	}

}
///EOF
