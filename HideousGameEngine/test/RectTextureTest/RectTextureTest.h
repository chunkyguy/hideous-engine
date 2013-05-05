//
//  RectTextureTest.h
//  HideousGameEngine
//
//  Created by Sid on 11/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__RectTextureTest__
#define __HideousGameEngine__RectTextureTest__
#include "TestTemplate.h"

#include <list>

namespace he{
	class RenderObject;
	class Texture;
	class TextureAtlas;
	class RectTextureSh;
	class VertexTex;
}

class RectTextureTest : public ITest{
public:
	~RectTextureTest();
	RectTextureTest(double w, double h);
	void Update(double dt);
	void Render();
	
private:
	void load_textures();
	void unload_textures();
	void handle_gestures();
	
	std::list<he::RenderObject *>render_objects_;
	std::list<he::Texture *>textures_;
	std::list<he::VertexTex *>vertex_datas_;
	he::TextureAtlas *atlas_;
	he::RectTextureSh *shader_;
};

#endif /* defined(__HideousGameEngine__RectTextureTest__) */
