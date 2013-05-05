//
//  TextureBigBangTest.h
//  HideousGameEngine
//
//  Created by Sid on 04/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__TextureBigBangTest__
#define __HideousGameEngine__TextureBigBangTest__
#include "TestTemplate.h"
#include "TexturedSprite.h"

namespace he{
	class RenderObject;
	class Texture;
	class TextureAtlas;
	class RectTextureSh;
	class VertexTex;
}

class TextureBigBangTest : public ITest{
public:
	~TextureBigBangTest();
	TextureBigBangTest(double width, double height);
	void Update(double dt);
	void Render();
	
private:
	const int kTotal_tex_sprites = 1000;
	typedef enum{kRunning, kDead} State;

	void load(GLKVector2 at);
	void unload();
	void handle_gesture();
	void load_assets();
	void unload_assets();

	he::RenderObject *sprite_;
	he::Texture *texture_;
	he::VertexTex *vertex_data_;
	he::TextureAtlas *atlas_;
	he::RectTextureSh *shader_;
	TexturedSprite **squares_;
	State state_;
	double delay_;
};
#endif /* defined(__HideousGameEngine__TextureBigBangTest__) */