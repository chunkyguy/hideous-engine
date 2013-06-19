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
#include <he/Utils/Screen.h>

/**	Handle transformations of a coordinate system
	Every object has its own coordinate system in reference to some parent coordinate system.
	At the root level there is the Device's coordinate system (the world space) which is located at {0, 0, Screen::z}
	
	Use GetMVP() to get the matrix that will help coordinates to world-space.
 */
namespace he{
	class Transform{
	public:
		/** Construct a new coordinate system transforms.
			@param position The position vector. Default is in the world-space, as it is the most used.
			@param rotation_angle The angle.
			@param rotation The rotation vector.
			@param scale The scale vector.
			@param parent transform system.
		 */
		explicit Transform(const GLKVector3 position = GLKVector3Make( 0.0f, 0.0f, g_Screen->z_),
						   const float rotation_angle = 0.0f,
						   const GLKVector3 rotation = GLKVector3Make( 1.0f, 1.0f, 1.0f),
						   const GLKVector3 scale = GLKVector3Make( 1.0f, 1.0f, 1.0f),
						   const Transform *parent = nullptr);
		
		/** Get the model-view matrix in world-space.
			Useful when batching several coordinates.
		 */
		GLKMatrix4 GetMV() const;
		
		/** Get the model-view-projection in world-space.
		 */
		GLKMatrix4 GetMVP() const;
		
		/** Get position in object space. */
		const GLKVector3 &GetPosition() const;

		/** Set position in object space. */
		void SetPosition(const GLKVector3 &position);
		/** Set position in world space. 
			z = Screen::z_
		 */
		void SetPosition(const GLKVector2 &position);

		/** Get rotation in object space */
		const GLKVector3 &GetRotation() const;

		/** Set rotation in object space */
		void SetRotation(const GLKVector3 &rotation);

		/** Get rotation angle */
		const float &GetRotationAngle() const;
		
		/** Set rotation angle */
		void SetRotationAngle(const float angle);
		
		/** Get scale in object space */
		const GLKVector3 &GetScale() const;

		/** Set scale in object space */
		void SetScale(const GLKVector3 &scale);

		/** Get the parent transform system */
		const Transform *GetParent() const;
		
		/** Set the new parent transform system
			I don't know why would someone need this.
		 */
		void SetParent(const Transform *parent);

		/** Get Address of vars, useful only when passing to animation system which works on addresses of objects
		 */
		GLKVector3 *GetPositionPtr();
		GLKVector3 *GetRotationPtr();
		float *GetRotationAnglePtr();
		GLKVector3 *GetScalePtr();
		
	private:
		GLKVector3 position_;
		float angle_;
		GLKVector3 rotation_;
		GLKVector3 scale_;
		const Transform *parent_;
	};
}
#endif /* defined(__HideousGameEngine__Transform__) */
