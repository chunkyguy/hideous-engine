//
//  MultiFontTest.h
//  HideousGameEngine
//
//  Created by Sid on 24/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__MultiFontTest__
#define __HideousGameEngine__MultiFontTest__
#include "TestTemplate.h"

namespace he{
	class Font;
};

class MultiFontTest : public ITest{
public:
	~MultiFontTest();
	MultiFontTest(double w, double h);
	void Update(double dt);
	void Render();
	
private:
	he::Font *courier_;
	he::Font *simsun_;
	
	void load_text();
	void unload_text();
	void handle_gestures();
};
#endif /* defined(__HideousGameEngine__MultiFontTest__) */
