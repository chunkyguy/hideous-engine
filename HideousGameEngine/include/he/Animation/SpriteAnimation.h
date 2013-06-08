//
//  SpriteAnimation.h
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_SpriteAnimation_h
#define HideousGameEngine_SpriteAnimation_h
#include <string>

#include <he/Animation/Animation.h>

namespace he {

	class TextureAtlas;
	class VertexTex;
	
	class SpriteAnimation : public Animation{
	public:
		SpriteAnimation(VertexTex **vertex_data,				/*Sprite to be rendered*/
						const TextureAtlas *atlas,			/*Atlas source*/
						const std::string &name,				/*Name of animation in the atlas*/
						const int final_frame_index	 = 0,	/*Frame index to be used when animation is over. Default 0*/
						const float fps = 24.0f);			/*Desired fps. Default is 24*/
		~SpriteAnimation();
		
	private:
		class Frame{
		public:
			Frame(VertexTex *vertex);
			~Frame();
			
			VertexTex *vertex_;
			Frame *next_;
		};
		
		void update(float dt);
		void next_frame();
		
		VertexTex **vertex_data_;
		VertexTex *final_vertex_data_;
		Frame *head_;
		Frame *tail_;
		Frame *active_frame_;			// The frame executing.
		float clock_;					// Clock resets after each frame execution. Relevant only when using delay.
		float delay_;					// Delay between each frame.
	};
	
}
#endif
