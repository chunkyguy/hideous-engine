//
//  Transform.cpp
//  HideousGameEngine
//
//  Created by Sid on 06/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/Screen.h>
#include <he/Utils/Transform.h>
#include <he/Utils/DebugHelper.h>

namespace he{
	Transform::Transform(const GLKVector3 position,
						 const float rotation_angle,
						 const GLKVector3 rotation,
						 const GLKVector3 scale,
						 const Transform *parent) :
	position_(position),
	angle_(rotation_angle),
	rotation_(rotation),
	scale_(scale),
	parent_(parent)
	{}

	
	GLKMatrix4 Transform::GetMV() const{
//		GLKMatrix4 parent_matrix = parent_ ? parent_->GetMV() : GLKMatrix4Identity;
//		GLKMatrix4 tMat = GLKMatrix4Translate(parent_matrix, position_.x, position_.y, position_.z);
//		GLKMatrix4 rMat = GLKMatrix4Rotate(parent_matrix, angle_, rotation_.x, rotation_.y, rotation_.z);
//		GLKMatrix4 sMat = GLKMatrix4Scale(parent_matrix, scale_.x, scale_.y, 1.0);

		GLKMatrix4 tMat = GLKMatrix4MakeTranslation(position_.x, position_.y, position_.z);
		GLKMatrix4 rMat = GLKMatrix4MakeRotation(angle_, rotation_.x, rotation_.y, rotation_.z);
		GLKMatrix4 sMat = GLKMatrix4MakeScale(scale_.x, scale_.y, 1.0);

		GLKMatrix4 mv = GLKMatrix4Multiply(GLKMatrix4Multiply(tMat, rMat), sMat);

//		he_Trace("GetMV: tMat:\n%@",tMat);
//		he_Trace("GetMV: rMat:\n%@",rMat);
//		he_Trace("GetMV: sMat:\n%@",sMat);
//		he_Trace("GetMV: mv:\n%@",mv);
		if(parent_){
			mv = GLKMatrix4Multiply(mv, parent_->GetMV());
			//			he_Trace("GetMV: mv':\n%@",mv);
		}
		return mv;
	}
	
	GLKMatrix4 Transform::GetMVP() const{
		return GLKMatrix4Multiply(he::g_Screen->projection_, GetMV());
	}

	const GLKVector3 &Transform::GetPosition() const{
		return position_;
	}
	void Transform::SetPosition(const GLKVector3 &position){
		position_ = position;
	}
	void Transform::SetPosition(const GLKVector2 &position){
		SetPosition(GLKVector3Make(position.x, position.y, g_Screen->z_));
	}

	const GLKVector3 &Transform::GetRotation() const{
		return rotation_;
	}
	void Transform::SetRotation(const GLKVector3 &rotation){
		rotation_ = rotation;
	}

	const float &Transform::GetRotationAngle() const{
		return angle_;
	}
	void Transform::SetRotationAngle(const float angle){
		angle_ = angle;
	}
	
	const GLKVector3 &Transform::GetScale() const{
		return scale_;
	}
	void Transform::SetScale(const GLKVector3 &scale){
		scale_ = scale;
	}
	
	const Transform *Transform::GetParent() const{
		return parent_;
	}
	void Transform::SetParent(const he::Transform *parent){
		parent_ = parent;
	}
	
	GLKVector3 *Transform::GetPositionPtr(){
		return &position_;
	}
	GLKVector3 *Transform::GetRotationPtr(){
		return &rotation_;
	}
	float *Transform::GetRotationAnglePtr(){
		return &angle_;
	}
	GLKVector3 *Transform::GetScalePtr(){
		return &scale_;
	}

}
///EOF
