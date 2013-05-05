
//
//  TestTemplate.h
//  HideousGameEngine
//
//  Created by Sid on 10/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
//	Test template for all the test cases
//	Has all kind of factories set up

#ifndef __HideousGameEngine__TestTemplate__
#define __HideousGameEngine__TestTemplate__
#include <GLKit/GLKMath.h>

class ITest{
public:
	virtual ~ITest(){}
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;

};
#endif /* defined(__HideousGameEngine__TestTemplate__) */