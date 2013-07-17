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
	class TextureVertex;
	
	class SpriteAnimation : public Animation{
	public:
		SpriteAnimation(TextureVertex **vertex_data,			/*Sprite data to be rendered*/
						const TextureAtlas *atlas,			/*Atlas source*/
						const std::string &name,				/*Name of animation in the atlas*/
						const int repeat_count = 1,			/*Num of repeat. -1 means infinite*/
						const int final_frame_index	 = 0,	/*Frame index to be used when animation is over. Default 0*/
						const float fps = 24.0f);			/*Desired fps. Default is 24*/
		~SpriteAnimation();

		void SetRepeatCount(int c);
		void SetFinalFrameIndex(int i);
		void SetFPS(float fps);
		
	private:
		// Internal structure. Data for each frame of the animation.
		class Frame{
		public:
			Frame(TextureVertex *vertex);
			~Frame();
			
			TextureVertex *vertex_;
			Frame *next_;
		};
		
		void update(float dt);
		void next_frame();
		
		TextureVertex **vertex_data_;
		TextureVertex *final_vertex_data_;

		Frame *head_;
		Frame *tail_;
		Frame *active_frame_;			// The frame executing.
		
		float clock_;					// Clock resets after each frame execution. Relevant only when using delay.
		float delay_;					// Delay between each frame.
		int repeat_count_;				// Num of repeats. -ve number will go on for a really long time.
										//	Ex: -1 will loop 4294967294 times (for a animatoin with just a single frame will run for 2+ years at 60 fps)
	};
	
}
#endif
