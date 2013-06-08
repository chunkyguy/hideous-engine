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

namespace he {
	class RenderObject;
	class RectTextureSh;
	class TextureAtlas;
	class VertexTex;
}

class FlashMovieAssets{
public:
	FlashMovieAssets(he::TextureAtlas *atlas, he::RectTextureSh *shader);
	~FlashMovieAssets();
	const he::TextureAtlas *GetAtlas() const;
	const he::RectTextureSh *GetShader() const;
	
private:
	he::TextureAtlas *atlas_;
	he::RectTextureSh *shader_;

};

class FlashMovie {
public:
	FlashMovie(const std::string &name, const FlashMovieAssets *asset, const int final_frame = 0, const float fps = 24.0f);
	~FlashMovie();
	void Update(double dt);
	void Render();

private:
	he::RenderObject *render_object_;
	he::VertexTex *vertex_data_;
};

#endif /* defined(__HideousGameEngine__FlashMovie__) */
