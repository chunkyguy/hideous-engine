//
//  Utils.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/Utils.h>

namespace he{
	
	//Set to next power of 2
	int NextPOT (int a){
		int rval = 1;
		while(rval<a)
			rval <<= 1;
		return rval;
	}
}
//EOF