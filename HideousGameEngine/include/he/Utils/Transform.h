//
//  Transform.h
//  HideousGameEngine
//
//  Created by Sid on 06/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__Transform__
#define __HideousGameEngine__Transform__

#include <he/Utils/GLKMath_Additions.h>

/**	Handle transformations of a coordinate system
 Every object has its own coordinate system in reference to some parent coordinate system.
 At the root level there is the Device's coordinate system (the world space) which is located at {0, 0, Screen::z}
 
 Use GetMVP() to get the matrix that will help coordinates to world-space.
 */
namespace he{
	struct Transform {
		/** Get position in object space. */
		GLKVector3 position; //{x, y, z}
		GLKVector4 rotation;	//{x, y, z, angle}
		GLKVector3 scale;	//{x, y, z}
		const Transform *parent;	
	};
	
	/** Construct a new coordinate system transforms.
	 @param position The position vector. Default is in the world-space, as it is the most used.
	 @param rotation The rotation vector + w component is the angle.
	 @param scale The scale vector.
	 @param parent transform system.
	 */
	Transform Transform_Create(const GLKVector3 position,
							  const GLKVector4 rotation = GLKVector4Make( 0.0f, 0.0f, 1.0f, 0.0f),
							  const GLKVector3 scale = GLKVector3Make( 1.0f, 1.0f, 1.0f),
							  const Transform *parent = nullptr);
	
	/** Construct a new coordinate system transforms.
	 @param position The position vector. Default is in the world-space, as it is the most used. 
	 position.z = Screen::z. Helpful when loading view to the world coord-system, instead of some other coord-system
	 @param rotation The rotation vector + w component is the angle.
	 @param scale The scale vector.
	 @param parent transform system.
	 */
	Transform Transform_Create(const GLKVector2 position,
							  const GLKVector4 rotation = GLKVector4Make( 0.0f, 0.0f, 1.0f, 0.0f),
							  const GLKVector3 scale = GLKVector3Make( 1.0f, 1.0f, 1.0f),
							  const Transform *parent = nullptr);

	/** Set the {x, y} component of the position */
	void Transform_SetPosition(Transform *slf, const GLKVector2 pos);
	/** Get the {x, y} component of the position */
	GLKVector2 Transform_GetPosition(const Transform &slf);
	

	Transform operator+(const Transform &one, const Transform &two);
	Transform operator-(const Transform &one, const Transform &two);
	Transform operator*(const Transform &one, float two);
	Transform operator*(float one, const Transform &two);
	
	/** Get the model-view matrix in world-space.
	 Useful when batching several coordinates.
	 */
	GLKMatrix4 Transform_GetMV(const Transform *slf);
	
	/** Get the model-view-projection in world-space.
	 */
	GLKMatrix4 Transform_GetMVP(const Transform *slf);
}
#endif /* defined(__HideousGameEngine__Transform__) */
