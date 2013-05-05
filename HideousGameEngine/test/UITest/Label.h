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
	class GlyphData;
	class VertexCol;
}

class Label{
public:
	Label(std::string text, he::Font *font);
	void SetText(std::string text);
	void SetColor(GLKVector4 color);
	he::VertexCol GetBox();
	void Render();

	he::Transform transform_;

private:
	std::string text_;
	he::Font *font_;
	GLKVector2 size_;
};
#endif /* defined(__HideousGameEngine__Label__) */
