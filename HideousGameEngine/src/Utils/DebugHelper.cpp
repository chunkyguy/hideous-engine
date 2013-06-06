//
//  DebugHelper.cpp
//  HideousGameEngine
//
//  Created by Sid on 06/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/DebugHelper.h>

void he_Trace(const char* s) {
	while (*s) {
		if (*s == '%' && *++s != '%'){
			throw std::runtime_error("invalid format string: missing arguments");
		}
		std::cout << *s++;
	}
}
