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
#include <he/Utils/GLKMath_Additions.h>

#include <he/Utils/Frame.h>

namespace he{
	class ColorShader;
	class ColorVertex;
	class Font;
	class RenderObject;
	class Text;
	class TextFactory;
	class TextShader;
	class Texture;
	class TextureAtlas;
	class TextureShader;
	class TextureVertex;
};

class ColObj{
public:
	~ColObj();
	ColObj(he::ColorShader *shader);
	void Render();
	
private:
	he::RenderObject *object_;
	he::ColorVertex *vert_;
	he::Transform transform_;
};

class TextureObj{
public:
	~TextureObj();
	TextureObj(he::TextureShader *shader, he::Texture *texture, he::TextureVertex *vert);
	void Render();
	
private:
	he::RenderObject *object_;
	he::Transform transform_;
};

class TextObj{
public:
	~TextObj();
	TextObj(he::TextFactory *factory);
	void Update(float dt);
	void Render();
	
private:
	he::Text *text_;
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
	he::ColorShader *col_sh_;
	// texture obj
	he::Texture *texture_;
	he::TextureVertex *vert_;
	he::TextureAtlas *atlas_;
	he::TextureShader *tex_sh_;
	
	// text obj
	he::TextFactory *txt_factory_;
	he::TextShader *txt_sh_;
};

#endif /* defined(__HEAssets__ObjectFactory__) */
