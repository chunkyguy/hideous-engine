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
	
	Transform Transform_Create(const GLKVector3 pos,
							  const GLKVector4 rot,
							  const GLKVector3 sc,
							  const Transform *p)
	{
		Transform t;
		t.position = pos;
		t.rotation = rot;
		t.scale = sc;
		t.parent = p;
		return t;
	}

	Transform Transform_Create(const GLKVector2 pos,
							  const GLKVector4 rot,
							  const GLKVector3 sc,
							  const Transform *p)
	{
		return Transform_Create(GLKVector3Make(pos.x, pos.y, g_Screen->z_), rot, sc, p);
	}
	
	GLKMatrix4 Transform_GetMV(const Transform *slf){

		GLKMatrix4 mv = GLKMatrix4Identity;
		mv = GLKMatrix4Translate(mv, slf->position.x, slf->position.y, slf->position.z);
		mv = GLKMatrix4Rotate(mv, slf->rotation.w, slf->rotation.x, slf->rotation.y, slf->rotation.z);
		mv = GLKMatrix4Scale(mv, slf->scale.x, slf->scale.y, slf->scale.z);
		if (slf->parent) {
			mv = GLKMatrix4Multiply(Transform_GetMV(slf->parent), mv);
		}
			
		
		
//		GLKMatrix4 pMat = (slf->parent) ? Transform_GetMV(slf->parent): GLKMatrix4Identity;
//		GLKMatrix4 tMat = GLKMatrix4MakeTranslation(slf->position.x, slf->position.y, slf->position.z);
//		GLKMatrix4 rMat = GLKMatrix4MakeRotation(slf->rotation.w, slf->rotation.x, slf->rotation.y, slf->rotation.z);
//		GLKMatrix4 sMat = GLKMatrix4MakeScale(slf->scale.x, slf->scale.y, slf->scale.z);
//		GLKMatrix4 mv = pMat * tMat * rMat * sMat;

		//GLKMatrix4 mv = sMat * rMat * tMat;
		//		GLKMatrix4 mv = GLKMatrix4Multiply(GLKMatrix4Multiply(tMat, rMat), sMat);
//		if(slf->parent){
//			mv = GLKMatrix4Multiply(Transform_GetMV(slf->parent), mv);
//		}
		return mv;
	}
	
	GLKMatrix4 Transform_GetMVP(const Transform *slf){
		return GLKMatrix4Multiply(he::g_Screen->projection_, Transform_GetMV(slf));
	}

	Transform operator+(const Transform &one, const Transform &two){
		assert(one.parent == two.parent);
		return Transform_Create(one.position+two.position,
							   one.rotation+two.rotation,
							   one.scale+two.scale);
	}
	Transform operator-(const Transform &one, const Transform &two){
		assert(one.parent == two.parent);
		return Transform_Create(one.position-two.position,
							   one.rotation-two.rotation,
							   one.scale-two.scale);
	}
	Transform operator*(const Transform &one, float two){
		return Transform_Create(one.position*two,
							   one.rotation*two,
							   one.scale*two);
	}
	Transform operator*(float one, const Transform &two){
		return two * one;
	}

	void Transform_SetPosition(Transform *slf, const GLKVector2 pos){
		slf->position.x = pos.x;
		slf->position.y = pos.y;
	}
	GLKVector2 Transform_GetPosition(const Transform &slf){
		return GLKVector2Make(slf.position.x, slf.position.y);
	}
	GLKVector3 Transform_GetLocalPosition(const Transform &slf, GLKVector3 world_position) {
		bool inv_result;
		GLKMatrix4 transform_inv = GLKMatrix4Invert(he::Transform_GetMV(&slf), &inv_result);
		assert(inv_result);	// the matrix should be invertible.
		GLKVector4 position4 = transform_inv * GLKVector4Make(world_position.x, world_position.y, world_position.z, 1.0f);
		return GLKVector3Make(position4.x, position4.y, position4.z);
	}

	void Transform_GetWorldCoordinates(const he::Transform &slf, const unsigned int count, GLKVector2 *vert) {
		GLKMatrix4 one_mv = he::Transform_GetMV(&slf);
		for (int i = 0; i < count; ++i) {
			GLKVector4 tmp = GLKMatrix4MultiplyVector4(one_mv, GLKVector4Make(vert[i].x, vert[i].y, 0.0f, 1.0f));
			vert[i] = GLKVector2Make(tmp.x, tmp.y);
		}
	}

	bool operator==(const Transform &one, const Transform &two) {
		return (one.parent		== two.parent	&&
				one.position		== two.position	&&
				one.rotation		== two.rotation	&&
				one.scale		==	two.scale);
	}
	std::ostream &operator<<(std::ostream &os, const Transform &trans) {
		os << "Position: " << trans.position;
		os << "Rotation: " << trans.rotation;
		os << "Scale: " << trans.scale;
		os << "Parent: " << (trans.parent != nullptr);
		return os;
	}

	
}
///EOF
