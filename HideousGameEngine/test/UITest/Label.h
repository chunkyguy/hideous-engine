//
//  Label.h
//  HideousGameEngine
//
//  Created by Sid on 13/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__Label__
#define __HideousGameEngine__Label__

#include <he/Utils/GLKMath_Additions.h>
#include <string>
#include <list>

#include <he/Utils/Transform.h>

namespace he{
	class Font;
	class Text;
	class ColorVertex;
}

class Label{
public:
	Label(std::string string, he::Font *font);
	~Label();
	void SetText(std::string string);
	void SetColor(GLKVector4 color);
	he::ColorVertex GetBox();
	void Render();

	he::Transform transform_;

private:
	he::Text *text_;
	he::Font *font_;
};
#endif /* defined(__HideousGameEngine__Label__) */
