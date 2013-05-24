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
#include <he/EventLoop/Gesture.h>


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
	void HandleGesture(const he::Gesture &gesture);
	
private:
	void load_textures();
	void unload_textures();
	
	std::list<he::RenderObject *>render_objects_;
	std::list<he::Texture *>textures_;
	std::list<he::VertexTex *>vertex_datas_;
	he::TextureAtlas *atlas_;
	he::Texture *atlas_texture_;
	he::RectTextureSh *shader_;
	he::GestureListener<RectTextureTest> *gesture_listener_;

#if defined(SPINE_TEXTURE_OBJECT)
	void load_goblin();
	void load_spineboy();
	GLKVector4 convert_to_tex_coords(GLKVector4 frame, GLKVector2 fullFrameSize);

	spine::Atlas* spine_atlas_;
#endif
};

#endif /* defined(__HideousGameEngine__RectTextureTest__) */
