//
//  Types.h
//  HideousGameEngine
//
//  Created by Sid on 18/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_Types_h
#define HideousGameEngine_Types_h

#include <gtest/internal/gtest-internal.h>

namespace he{
	/** A 32 bit floating-point num used for operations like cmp */
	typedef testing::internal::FloatingPoint<float> F32;
	
	/** Compare two floating point numbers */
	inline bool F32Eq(float a, float b){
		F32 a_(a);
		F32 b_(b);
		return a_.AlmostEquals(b_);
	}
}
#endif
