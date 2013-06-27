//
//  Sprite.h
//  HideousGameEngine
//
//  Created by Sid on 20/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_Sprite_h
#define HideousGameEngine_Sprite_h
#include <he/UI/View.h>
#include <he/Utils/Frame.h>

namespace he {
	class RenderObject;
	class TextureAtlas;
	class TextureVertex;
	class TextureShader;
	
	class Sprite : public View{
	public:
		Sprite(const Frame frame, const std::string &animation_name, const TextureShader *shader, const TextureAtlas *atlas,
			   const int repeat_count = -1, const int final_frame = 0, const float fps = 24.0f);
		virtual ~Sprite();
		
	protected:
		virtual void update(float dt);
		virtual void render();
		
		TextureVertex *vertex_;
		RenderObject *render_object_;
	};
}

#endif
