//
//  GLKMath_Additions.cpp
//  HideousGameEngine
//
//  Created by Sid on 08/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/GLKMath_Additions.h>

std::ostream &operator<<(std::ostream &os, GLKVector2 vec){
	os << "{ " << vec.x << ", " << vec.y << " }";
	return os;
}
std::ostream &operator<<(std::ostream &os, GLKVector3 vec){
	os << "{ " << vec.x << ", " << vec.y << ", " << vec.z << " }";
	return os;
}
std::ostream &operator<<(std::ostream &os, GLKVector4 vec){
	os << "{{ " << vec.x << ", " << vec.y << " },{ " << vec.z << ", " << vec.w << " }}";
	return os;
}

///EOF
