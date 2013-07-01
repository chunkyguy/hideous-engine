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

	/** Sprite object.
	 @brief		Sprite is an animated texture object. The texture has to be provided as an atlas.
	 */
	class Sprite : public View{
	public:
		/**	Construct Sprite.
		 @note	Use ImageFactory to create sprites in a easy way.
		 @param frame			The frame.
		 @param animation_name	The symbol stored on the atlas data file. Only expecting a flash like naming convention for now,
		 @param shader			The texture-shader.
		 @param atlas			The atlas
		 @param repeat_count		Number of times the animation should run back to back. Default is infinite (= -1).
		 @param final_frame		What frame to display when the animation is over. Default is the first frame (= 0).
		 @param fps				The speed of the animation. Default is 24 FPS.
		 */
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
