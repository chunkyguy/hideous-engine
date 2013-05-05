//
//  RectTextTest.h
//  HideousGameEngine
//
//  Created by Sid on 13/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__RectTextTest__
#define __HideousGameEngine__RectTextTest__
#include "TestTemplate.h"

namespace he{
	class Font;
	class Text;
}

class RectTextTest : public ITest{
public:
	~RectTextTest();
	RectTextTest(double width, double height);
	void Update(double dt);
	void Render();
	
private:
	void load_text();
	void unload_text();
	void handle_gestures();

	he::Font *font_;
	he::Text *text_;
};
#endif /* defined(__HideousGameEngine__RectTextTest__) */
