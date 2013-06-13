//
//  UITest.h
//  HideousGameEngine
//
//  Created by Sid on 26/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

// TODO: UISlider
#ifndef __HideousGameEngine__UITest__
#define __HideousGameEngine__UITest__
#include "TestTemplate.h"

#include <he/Utils/Asset.h>
namespace he{
	class Texture;
	class TextureShader;
	class TextureVertex;
	class TextureAtlas;
	
	namespace ui{
		class View;
	}
}

class UITest : public ITest{
public:
	~UITest();
	UITest(float width, float height);
	void Update(float dt);
	void Render();
	
private:
	he::ui::View *view_;
	he::Asset<he::Texture> texture_;
	he::Asset<he::TextureVertex> vertex_;
	he::Asset<he::TextureShader> shader_;
};


#endif /* defined(__HideousGameEngine__UITest__) */
