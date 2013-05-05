//
//  Label.h
//  HideousGameEngine
//
//  Created by Sid on 13/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__Label__
#define __HideousGameEngine__Label__

#include <GLKit/GLKMath.h>
#include <string>
#include <list>

#include <he/Utils/Transform.h>

namespace he{
	class Font;
	class Text;
	class VertexCol;
}

class Label{
public:
	Label(std::string string, he::Font *font);
	~Label();
	void SetText(std::string string);
	void SetColor(GLKVector4 color);
	he::VertexCol GetBox();
	void Render();

	he::Transform transform_;

private:
	he::Text *text_;
	he::Font *font_;
};
#endif /* defined(__HideousGameEngine__Label__) */
