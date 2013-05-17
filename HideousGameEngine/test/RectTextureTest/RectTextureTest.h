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

//#define SPINE_TEXTURE_OBJECT
#if defined(SPINE_TEXTURE_OBJECT)
#include "spine.h"
 
#endif

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

#if defined(SPINE_TEXTURE_OBJECT)
	void load_goblin();
	void load_spineboy();
	GLKVector4 convert_to_tex_coords(GLKVector4 frame, GLKVector2 fullFrameSize);

	spine::Atlas* spine_atlas_;
#endif
};

#endif /* defined(__HideousGameEngine__RectTextureTest__) */
