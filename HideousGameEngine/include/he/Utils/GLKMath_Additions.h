//
//  Math.h
//  HideousGameEngine
//
//  Created by Sid on 22/05/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

// Extension of work of following author:
// ORIGINAL LICENSE:
/*
 Copyright (c) 2011, Darknoon / Andrew Pouliot
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer
 in the documentation and/or other materials provided with the distribution.
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef HideousGameEngine_Math_h
#define HideousGameEngine_Math_h

#include <GLKit/GLKMath.h>

#ifdef __cplusplus


////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: GLKVector2
////////////////////////////////////////////////////////////////////////////////////////////////////

//Unary operators
inline GLKVector2 operator - (const GLKVector2& v) {
	return GLKVector2Negate(v);
}

//Binary operators

inline GLKVector2 operator + (const GLKVector2& left, const GLKVector2& right) {
	return GLKVector2Add(left, right);
}

inline GLKVector2 operator - (const GLKVector2& left, const GLKVector2& right) {
	return GLKVector2Subtract(left, right);
}

inline GLKVector2 operator * (const GLKVector2& left, const GLKVector2& right) {
	return GLKVector2Multiply(left, right);
}

inline GLKVector2 operator / (const GLKVector2& left, const GLKVector2& right) {
	return GLKVector2Divide(left, right);
}

inline GLKVector2 operator + (const GLKVector2& left, const float& right) {
	return GLKVector2AddScalar(left, right);
}

// V - k
inline GLKVector2 operator - (const GLKVector2& left, const float& right) {
	return GLKVector2SubtractScalar(left, right);
}

// V * k
inline GLKVector2 operator * (const GLKVector2& left, const float& right) {
	return GLKVector2MultiplyScalar(left, right);
}

// k * V
inline GLKVector2 operator * (const float& left, const GLKVector2& right) {
	return GLKVector2MultiplyScalar(right, left);
}

inline GLKVector2 operator / (const GLKVector2& left, const float& right) {
	return GLKVector2DivideScalar(left, right);
}

inline bool operator == (const GLKVector2& left, const GLKVector2& right) {
	return GLKVector2AllEqualToVector2(left, right);
}

inline bool operator != (const GLKVector2& left, const GLKVector2& right) {
	return !GLKVector2AllEqualToVector2(left, right);
}

inline bool operator >= (const GLKVector2& left, const GLKVector2& right) {
	return GLKVector2AllGreaterThanOrEqualToVector2(left, right);
}

inline bool operator > (const GLKVector2& left, const GLKVector2& right) {
	return GLKVector2AllGreaterThanVector2(left, right);
}

inline bool operator <= (const GLKVector2& left, const GLKVector2& right) {
	return !GLKVector2AllGreaterThanVector2(left, right);
}

inline bool operator < (const GLKVector2& left, const GLKVector2& right) {
	return !GLKVector2AllGreaterThanOrEqualToVector2(left, right);
}

//Assigning binary operators

inline GLKVector2 operator += (GLKVector2& left, const GLKVector2& right) {
	return (left = GLKVector2Add(left, right));
}

inline GLKVector2 operator -= (GLKVector2& left, const GLKVector2& right) {
	return (left = GLKVector2Subtract(left, right));
}

inline GLKVector2 operator *= (GLKVector2& left, const GLKVector2& right) {
	return (left = GLKVector2Multiply(left, right));
}

inline GLKVector2 operator /= (GLKVector2& left, const GLKVector2& right) {
	return (left = GLKVector2Divide(left, right));
}

inline GLKVector2 operator += (GLKVector2& left, const float& right) {
	return (left = GLKVector2AddScalar(left, right));
}

inline GLKVector2 operator -= (GLKVector2& left, const float& right) {
	return (left = GLKVector2SubtractScalar(left, right));
}

inline GLKVector2 operator *= (GLKVector2& left, const float& right) {
	return (left = GLKVector2MultiplyScalar(left, right));
}

inline GLKVector2 operator /= (GLKVector2& left, const float& right) {
	return (left = GLKVector2DivideScalar(left, right));
}

//Convenience Functions

//inline GLKVector2 max(const GLKVector2 &a, const GLKVector2 &b) {
//	return GLKVector2Maximum(a, b);
//}
//
//inline GLKVector2 min(const GLKVector2 &a, const GLKVector2 &b) {
//	return GLKVector2Minimum(a, b);
//}
//
//inline float length(const GLKVector2 &v) {
//	return GLKVector2Length(v);
//}
//
//inline float dot(const GLKVector2 &a, const GLKVector2 &b) {
//	return GLKVector2DotProduct(a, b);
//}
//
//inline float lengthSquared(const GLKVector2 &v) {
//	return dot(v, v);
//}
//
//inline GLKVector2 lerp(GLKVector2 a, GLKVector2 b, float t) {
//	return GLKVector2Lerp(a, b, t);
//}
//
//inline GLKVector2 project(GLKVector2 vectorToProject, GLKVector2 projectionVector) {
//	return GLKVector2Project(vectorToProject, projectionVector);
//}
//
//inline GLKVector2 normalize(const GLKVector2 &v) {
//	return GLKVector2Normalize(v);
//}

////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: GLKVector3
////////////////////////////////////////////////////////////////////////////////////////////////////

//Unary operators

inline GLKVector3 operator - (const GLKVector3& v) {
	return GLKVector3Negate(v);
}

//Binary operators

inline GLKVector3 operator + (const GLKVector3& left, const GLKVector3& right) {
	return GLKVector3Add(left, right);
}

inline GLKVector3 operator - (const GLKVector3& left, const GLKVector3& right) {
	return GLKVector3Subtract(left, right);
}

inline GLKVector3 operator * (const GLKVector3& left, const GLKVector3& right) {
	return GLKVector3Multiply(left, right);
}

inline GLKVector3 operator / (const GLKVector3& left, const GLKVector3& right) {
	return GLKVector3Divide(left, right);
}

inline GLKVector3 operator + (const GLKVector3& left, const float& right) {
	return GLKVector3AddScalar(left, right);
}

// V - k
inline GLKVector3 operator - (const GLKVector3& left, const float& right) {
	return GLKVector3SubtractScalar(left, right);
}

// V * k
inline GLKVector3 operator * (const GLKVector3& left, const float& right) {
	return GLKVector3MultiplyScalar(left, right);
}

// k * V
inline GLKVector3 operator * (const float& left, const GLKVector3& right) {
	return GLKVector3MultiplyScalar(right, left);
}

inline GLKVector3 operator / (const GLKVector3& left, const float& right) {
	return GLKVector3DivideScalar(left, right);
}

inline bool operator == (const GLKVector3& left, const GLKVector3& right) {
	return GLKVector3AllEqualToVector3(left, right);
}

inline bool operator != (const GLKVector3& left, const GLKVector3& right) {
	return !GLKVector3AllEqualToVector3(left, right);
}

inline bool operator >= (const GLKVector3& left, const GLKVector3& right) {
	return GLKVector3AllGreaterThanOrEqualToVector3(left, right);
}

inline bool operator > (const GLKVector3& left, const GLKVector3& right) {
	return GLKVector3AllGreaterThanVector3(left, right);
}

inline bool operator <= (const GLKVector3& left, const GLKVector3& right) {
	return !GLKVector3AllGreaterThanVector3(left, right);
}

inline bool operator < (const GLKVector3& left, const GLKVector3& right) {
	return !GLKVector3AllGreaterThanOrEqualToVector3(left, right);
}

//Assigning binary operators

inline GLKVector3 operator += (GLKVector3& left, const GLKVector3& right) {
	return (left = GLKVector3Add(left, right));
}

inline GLKVector3 operator -= (GLKVector3& left, const GLKVector3& right) {
	return (left = GLKVector3Subtract(left, right));
}

inline GLKVector3 operator *= (GLKVector3& left, const GLKVector3& right) {
	return (left = GLKVector3Multiply(left, right));
}

inline GLKVector3 operator /= (GLKVector3& left, const GLKVector3& right) {
	return (left = GLKVector3Divide(left, right));
}

inline GLKVector3 operator += (GLKVector3& left, const float& right) {
	return (left = GLKVector3AddScalar(left, right));
}

inline GLKVector3 operator -= (GLKVector3& left, const float& right) {
	return (left = GLKVector3SubtractScalar(left, right));
}

inline GLKVector3 operator *= (GLKVector3& left, const float& right) {
	return (left = GLKVector3MultiplyScalar(left, right));
}

inline GLKVector3 operator /= (GLKVector3& left, const float& right) {
	return (left = GLKVector3DivideScalar(left, right));
}

//Convenience Functions

//inline GLKVector3 max(const GLKVector3 &a, const GLKVector3 &b) {
//	return GLKVector3Maximum(a, b);
//}
//
//inline GLKVector3 min(const GLKVector3 &a, const GLKVector3 &b) {
//	return GLKVector3Minimum(a, b);
//}
//
//inline float length(const GLKVector3 &v) {
//	return GLKVector3Length(v);
//}
//
//inline float dot(const GLKVector3 &a, const GLKVector3 &b) {
//	return GLKVector3DotProduct(a, b);
//}
//
//inline float lengthSquared(const GLKVector3 &v) {
//	return dot(v, v);
//}
//
//inline GLKVector3 lerp(GLKVector3 a, GLKVector3 b, float t) {
//	return GLKVector3Lerp(a, b, t);
//}
//
//inline GLKVector3 project(GLKVector3 vectorToProject, GLKVector3 projectionVector) {
//	return GLKVector3Project(vectorToProject, projectionVector);
//}
//
//inline GLKVector3 normalize(const GLKVector3 &v) {
//	return GLKVector3Normalize(v);
//}
//
//inline GLKVector3 cross(const GLKVector3 &a, const GLKVector3 &b) {
//	return GLKVector3CrossProduct(a, b);
//}

////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: GLKVector4
////////////////////////////////////////////////////////////////////////////////////////////////////
inline GLKVector4 operator - (const GLKVector4& v) {
	return GLKVector4Negate(v);
}

//Binary operators

inline GLKVector4 operator + (const GLKVector4& left, const GLKVector4& right) {
	return GLKVector4Add(left, right);
}

inline GLKVector4 operator - (const GLKVector4& left, const GLKVector4& right) {
	return GLKVector4Subtract(left, right);
}

inline GLKVector4 operator * (const GLKVector4& left, const GLKVector4& right) {
	return GLKVector4Multiply(left, right);
}

inline GLKVector4 operator / (const GLKVector4& left, const GLKVector4& right) {
	return GLKVector4Divide(left, right);
}

inline GLKVector4 operator + (const GLKVector4& left, const float& right) {
	return GLKVector4AddScalar(left, right);
}

// V - k
inline GLKVector4 operator - (const GLKVector4& left, const float& right) {
	return GLKVector4SubtractScalar(left, right);
}

// V * k
inline GLKVector4 operator * (const GLKVector4& left, const float& right) {
	return GLKVector4MultiplyScalar(left, right);
}

// k * V
inline GLKVector4 operator * (const float& left, const GLKVector4& right) {
	return GLKVector4MultiplyScalar(right, left);
}

inline GLKVector4 operator / (const GLKVector4& left, const float& right) {
	return GLKVector4DivideScalar(left, right);
}

inline bool operator == (const GLKVector4& left, const GLKVector4& right) {
	return GLKVector4AllEqualToVector4(left, right);
}

inline bool operator != (const GLKVector4& left, const GLKVector4& right) {
	return !GLKVector4AllEqualToVector4(left, right);
}

inline bool operator >= (const GLKVector4& left, const GLKVector4& right) {
	return GLKVector4AllGreaterThanOrEqualToVector4(left, right);
}

inline bool operator > (const GLKVector4& left, const GLKVector4& right) {
	return GLKVector4AllGreaterThanVector4(left, right);
}

inline bool operator <= (const GLKVector4& left, const GLKVector4& right) {
	return !GLKVector4AllGreaterThanVector4(left, right);
}

inline bool operator < (const GLKVector4& left, const GLKVector4& right) {
	return !GLKVector4AllGreaterThanOrEqualToVector4(left, right);
}

//Assigning binary operators

inline GLKVector4 operator += (GLKVector4& left, const GLKVector4& right) {
	return (left = GLKVector4Add(left, right));
}

inline GLKVector4 operator -= (GLKVector4& left, const GLKVector4& right) {
	return (left = GLKVector4Subtract(left, right));
}

inline GLKVector4 operator *= (GLKVector4& left, const GLKVector4& right) {
	return (left = GLKVector4Multiply(left, right));
}

inline GLKVector4 operator /= (GLKVector4& left, const GLKVector4& right) {
	return (left = GLKVector4Divide(left, right));
}

inline GLKVector4 operator += (GLKVector4& left, const float& right) {
	return (left = GLKVector4AddScalar(left, right));
}

inline GLKVector4 operator -= (GLKVector4& left, const float& right) {
	return (left = GLKVector4SubtractScalar(left, right));
}

inline GLKVector4 operator *= (GLKVector4& left, const float& right) {
	return (left = GLKVector4MultiplyScalar(left, right));
}

inline GLKVector4 operator /= (GLKVector4& left, const float& right) {
	return (left = GLKVector4DivideScalar(left, right));
}

//Convenience Functions

//inline GLKVector4 max(const GLKVector4 &a, const GLKVector4 &b) {
//	return GLKVector4Maximum(a, b);
//}
//
//inline GLKVector4 min(const GLKVector4 &a, const GLKVector4 &b) {
//	return GLKVector4Minimum(a, b);
//}
//
//inline float length(const GLKVector4 &v) {
//	return GLKVector4Length(v);
//}
//
//inline float dot(const GLKVector4 &a, const GLKVector4 &b) {
//	return GLKVector4DotProduct(a, b);
//}
//
//inline float lengthSquared(const GLKVector4 &v) {
//	return dot(v, v);
//}
//
//inline GLKVector4 lerp(GLKVector4 a, GLKVector4 b, float t) {
//	return GLKVector4Lerp(a, b, t);
//}
//
//inline GLKVector4 project(GLKVector4 vectorToProject, GLKVector4 projectionVector) {
//	return GLKVector4Project(vectorToProject, projectionVector);
//}
//
//inline GLKVector4 normalize(const GLKVector4 &v) {
//	return GLKVector4Normalize(v);
//}
//
//inline GLKVector4 cross(const GLKVector4 &a, const GLKVector4 &b) {
//	return GLKVector4CrossProduct(a, b);
//}

////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: GLKMatrix2
////////////////////////////////////////////////////////////////////////////////////////////////////
inline GLKVector2 operator * (const GLKMatrix2& left, const GLKVector2& right) {
	return GLKVector2Make(right.x * left.m00 + right.y * left.m01,
						  right.x * left.m10 + right.y * left.m11);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: GLKMatrix3
////////////////////////////////////////////////////////////////////////////////////////////////////
inline GLKMatrix3 operator * (const GLKMatrix3& left, const GLKMatrix3& right) {
	return GLKMatrix3Multiply(left, right);
}

inline GLKMatrix3 operator + (const GLKMatrix3& left, const GLKMatrix3& right) {
	return GLKMatrix3Add(left, right);
}

inline GLKMatrix3 operator - (const GLKMatrix3& left, const GLKMatrix3& right) {
	return GLKMatrix3Subtract(left, right);
}

inline GLKVector3 operator * (const GLKMatrix3& left, const GLKVector3& right) {
	//TODO: which should we use?
	return GLKMatrix3MultiplyVector3(left, right);
	//return GLKMatrix3MultiplyVector3WithTranslation(left, right);
}

//	inline GLKVector3 operator * (const GLKMatrix3& left, const GLKVector2& right) {
//		//TODO: which should we use?
//		return GLKMatrix3MultiplyVector3(left, (GLKVector3){right.x, right.y, 0.0f});
//		//return GLKMatrix3MultiplyVector3WithTranslation(left, right);
//	}

////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: GLKMatrix4
////////////////////////////////////////////////////////////////////////////////////////////////////
inline GLKMatrix4 operator * (const GLKMatrix4& left, const GLKMatrix4& right) {
	return GLKMatrix4Multiply(left, right);
}

inline GLKMatrix4 operator + (const GLKMatrix4& left, const GLKMatrix4& right) {
	return GLKMatrix4Add(left, right);
}

inline GLKMatrix4 operator - (const GLKMatrix4& left, const GLKMatrix4& right) {
	return GLKMatrix4Subtract(left, right);
}

inline GLKVector4 operator * (const GLKMatrix4& left, const GLKVector4& right) {
	//TODO: which should we use?
	return GLKMatrix4MultiplyVector4(left, right);
	//return GLKMatrix4MultiplyVector3WithTranslation(left, right);
}

inline GLKVector3 operator * (const GLKMatrix4& left, const GLKVector3& right) {
	//TODO: which should we use?
	return GLKMatrix4MultiplyVector3(left, right);
	//return GLKMatrix4MultiplyVector3WithTranslation(left, right);
}

//	inline GLKVector3 operator * (const GLKMatrix4& left, const GLKVector2& right) {
//		//TODO: which should we use?
//		return GLKMatrix4MultiplyVector3(left, (GLKVector3){right.x, right.y, 0.0f});
//		//return GLKMatrix4MultiplyVector3WithTranslation(left, right);
//	}

////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: GLKQuaternion
////////////////////////////////////////////////////////////////////////////////////////////////////
//Binary operators

inline GLKQuaternion operator + (const GLKQuaternion& left, const GLKQuaternion& right) {
	return GLKQuaternionAdd(left, right);
}
inline GLKQuaternion operator - (const GLKQuaternion& left, const GLKQuaternion& right) {
	return GLKQuaternionSubtract(left, right);
}

inline GLKQuaternion operator * (const GLKQuaternion& left, const GLKQuaternion& right) {
	return GLKQuaternionMultiply(left, right);
}

//Assigning operators

inline GLKQuaternion operator += (GLKQuaternion& left, const GLKQuaternion& right) {
	return (left = GLKQuaternionAdd(left, right));
}
inline GLKQuaternion operator -= (GLKQuaternion& left, const GLKQuaternion& right) {
	return (left = GLKQuaternionSubtract(left, right));
}

inline GLKQuaternion operator *= (GLKQuaternion& left, const GLKQuaternion& right) {
	return (left = GLKQuaternionMultiply(left, right));
}


//Convenience functions

//inline float length (GLKQuaternion& q) {
//	return GLKQuaternionLength(q);
//}
//
//inline GLKQuaternion slerp (GLKQuaternion& a, GLKQuaternion& b, float t) {
//	return GLKQuaternionSlerp(a, b, t);
//}


#endif
#endif