//
//  FlashTest.h
//  HideousGameEngine
//
//  Created by Sid on 06/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__FlashTest__
#define __HideousGameEngine__FlashTest__

#include "../TestTemplate.h"

class FlashTest : public ITest {
public:
	FlashTest(float w, float h);
	~FlashTest();
	void Update(float dt);
	void Render();
};

#endif /* defined(__HideousGameEngine__FlashTest__) */
