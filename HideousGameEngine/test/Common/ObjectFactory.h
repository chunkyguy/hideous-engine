//
//  ObjectFactory.h
//  HEAssets
//
//  Created by Sid on 28/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HEAssets__ObjectFactory__
#define __HEAssets__ObjectFactory__

#include <list>
#include <GLKit/GLKMath.h>

namespace he{
	class Font;
	class GlyphData;
	class RectColorSh;
	class RectTextureSh;
	class RenderObject;
	class Texture;
	class TextureAtlas;
	class VertexCol;
	class VertexTex;
};

class ColObj{
public:
	~ColObj();
	ColObj(he::RectColorSh *shader);
	void Render();
	
private:
	he::RenderObject *object_;
	he::VertexCol *vert_;
	GLKVector2 pos_;
};

class TextureObj{
public:
	~TextureObj();
	TextureObj(he::RectTextureSh *shader, he::Texture *texture, 	he::VertexTex *vert);
	void Render();
	
private:
	he::RenderObject *object_;
	GLKVector2 pos_;
};

class TextObj{
public:
	~TextObj();
	TextObj(he::Font *font);
	void Render();
	
private:
	std::list<he::GlyphData *> glyph_data_;
	GLKVector2 pos_;
};

class ObjectFactory{
public:
	~ObjectFactory();
	ObjectFactory();
	ColObj *CreateColoredObject();
	TextureObj *CreateTexturedObject();
	TextObj *CreateTextObject();

private:
	void load_assets();
	void unload_assets();
	
	// colored obj
	he::RectColorSh *col_sh_;
	// texture obj
	he::Texture *texture_;
	he::VertexTex *vert_;
	he::TextureAtlas *atlas_;
	he::RectTextureSh *tex_sh_;
	
	// text obj
	he::Font *font_;
};

#endif /* defined(__HEAssets__ObjectFactory__) */
