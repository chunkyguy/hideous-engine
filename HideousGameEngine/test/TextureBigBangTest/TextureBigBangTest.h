//
//  TextureBigBangTest.h
//  HideousGameEngine
//
//  Created by Sid on 04/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__TextureBigBangTest__
#define __HideousGameEngine__TextureBigBangTest__
#include <he/Main/HideousGame.h>

#include <he/EventLoop/Gesture.h>

#include "TexturedSprite.h"

namespace he{
	class RenderObject;
	class Texture;
	class TextureAtlas;
	class TextureShader;
	class TextureVertex;
}

class TextureBigBangTest : public he::Game{
public:
	~TextureBigBangTest();
	TextureBigBangTest(GLKVector3 cc);
	void HandleGesture(const he::Gesture &gesture);
	
private:
	const int kTotal_tex_sprites = 1000;
	typedef enum{kRunning, kDead} State;

	void update(float dt);
	void render();
	void load(GLKVector2 at);
	void unload();
	void load_assets();
	void unload_assets();

	he::RenderObject *sprite_;
	he::Texture *texture_;
	he::TextureVertex *vertex_data_;
	he::TextureAtlas *atlas_;
	he::TextureShader *shader_;
	TexturedSprite **squares_;
	State state_;
	float delay_;
	he::GestureListener<TextureBigBangTest> *gesture_listener_;
};
#endif /* defined(__HideousGameEngine__TextureBigBangTest__) */
