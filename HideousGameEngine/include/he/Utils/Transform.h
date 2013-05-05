//
//  Transform.h
//  HideousGameEngine
//
//  Created by Sid on 06/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__Transform__
#define __HideousGameEngine__Transform__
#include <GLKit/GLKMath.h>
namespace he{
	class Transform{
	public:
		Transform(GLKVector2 position = GLKVector2Make(0,0), double r = 0, GLKVector2 s = GLKVector2Make(1.0,1.0));
		Transform(const Transform &other);
		void operator=(const Transform &other);
		GLKMatrix4 GetMV();
		GLKMatrix4 GetMVP();
		const GLKVector2 &GetPosition() const;
		void SetPosition(const GLKVector2 &position);
		const double GetRotation() const;
		void SetRotation(const double rotation);
		const GLKVector2 &GetScale() const;
		void SetScale(const GLKVector2 &scale);

		GLKVector2 position_;
		double rotation_;
		GLKVector2 scale_;
	};
}
#endif /* defined(__HideousGameEngine__Transform__) */
