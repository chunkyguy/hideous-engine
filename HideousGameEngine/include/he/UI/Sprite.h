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
#include <he/Animation/Animation.h>

namespace he {
	class RenderObject;
	class TextureAtlas;
	class TextureVertex;
	class TextureShader;
	class SpriteAnimation;
	class SpriteAnimationData;

	/** Sprite object.
	 @brief		Sprite is an animated texture object. The texture has to be provided as an atlas.
	 */
	class Sprite {
	public:
		/**	Construct Sprite.
		 @param data				The sprite animation data.
		 @param shader			The texture-shader.
		 @param atlas			The atlas
		 @param repeat_count		Repeat count. -1 means infinite loop.
		 @param listener			Add a listener for the internal animation.
		 @param final_frame		The final frame to display when the animation is over.
		 @param fps				The speed of the animation. Default is 24 FPS.
		 @note	The sprite is loaded by default in paused state. Call StartAnimation to start the animation.
		 */
		Sprite(const SpriteAnimationData *data,
			   const TextureShader *shader, const TextureAtlas *atlas,
			   const int repeat_count = -1, AnimationListenable *listener = nullptr,
			   const int final_frame = 0, const float fps = 24.0f);
		~Sprite();

		/**
		 *	Get the Animation::ID associated with the internal animation.
		 *	@return	The Animation::ID
		 */
		Animation::ID GetID() const;
		
		/**
		 *	Render
		 *
		 *	@param	transform	The transform at which to render.
		 */
		void Render(const Transform &transform);

		GLKVector2 GetSize() const;
		
		
		void GoToFrameNumber(unsigned int frame_num);
		unsigned int GetCurrentFrameNumber() const;

		unsigned int GetFrameCount() const;

		/**
		 *	Actually start animating. This method avoids situation where the caller just wishes to create an object 
		 *	and run it at some time later.
		 */
		void StartAnimation();

	private:
		GLKVector2 size_;
		TextureVertex *vertex_;
		RenderObject *render_object_;
		SpriteAnimation *animation_;
		Animation::ID anim_id_;
	};


	namespace sprite {
		SpriteAnimationData *Create(const TextureAtlas *texture_atlas,
									const std::string &region);
		Sprite *Create(const SpriteAnimationData *data, 
					   const TextureShader *shader, const TextureAtlas *texture_atlas,
					   const int repeat_count = -1, AnimationListenable *listener = nullptr,
					   const int final_frame = 0, const float fps = 24.0f);
	}
	
	class SpriteView : public View {
	public:
		SpriteView(const Transform &transform, Sprite *sprite);
		virtual void Update(float dt);
		virtual void Render();
		virtual GLKVector2 GetSize() const;
		
	private:
		Sprite *sprite_;
	};
}

#endif
