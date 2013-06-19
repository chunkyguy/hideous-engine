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
std::ostream &operator<<(std::ostream &os, GLKMatrix4 mat){
	for (int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j){
			os << mat.m[i*4 + j] << " ";
		}
		os << std::endl;
	}
	return os;
}

///EOF
