//
//  FlashMovie.h
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__FlashMovie__
#define __HideousGameEngine__FlashMovie__
#include <string>

#include <he/Utils/GLKMath_Additions.h>

namespace he {
	class RenderObject;
	class TextureShader;
	class TextureAtlas;
	class TextureVertex;
	class SpriteAnimationData;
}

class FlashMovieAssets{
public:
	FlashMovieAssets(he::TextureAtlas *atlas, he::TextureShader *shader, const std::string &name);
	~FlashMovieAssets();
	const he::TextureAtlas *GetAtlas() const;
	const he::TextureShader *GetShader() const;
	const he::SpriteAnimationData *GetData() const;
	
private:
	he::TextureAtlas *atlas_;
	he::TextureShader *shader_;
	he::SpriteAnimationData *data_;
};

class FlashMovie {
public:
	FlashMovie(const std::string &name,
			   const FlashMovieAssets *asset,
			   const GLKVector2 &position = GLKVector2Make(0.0f, 0.0f),
			   const int final_frame = 0,
			   const float fps = 24.0f);
	~FlashMovie();
	void Update(double dt);
	void Render();
	void TouchPoint(const GLKVector2 &point);
	
private:	
	GLKVector3 angle_;
	GLKVector2 position_;
	he::RenderObject *render_object_;
	he::TextureVertex *vertex_data_;
};

#endif /* defined(__HideousGameEngine__FlashMovie__) */
