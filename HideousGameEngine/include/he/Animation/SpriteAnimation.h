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
	
	class SpriteAnimationData {
	public:
		// Internal structure. Data for each frame of the animation.
		class Frame{
		public:
			Frame(TextureVertex *vertex);
			~Frame();
			
			TextureVertex *vertex_;
			Frame *next_;
		};

		/**
		 *	@param atlas		Atlas source
		 *	@param name		Name of animation in the atlas
		 */
		SpriteAnimationData(const TextureAtlas *atlas, const std::string &name);
		~SpriteAnimationData();
		
		/**
		 *	Get total frames in this animation.
		 *
		 *	@return	Total frame count.
		 */
		unsigned int GetFrameCount() const;

		/**
		 *	Returns the frame at specified index.
		 *
		 *	@param	frame_num  The frame number.
		 *
		 *	@return	Frame or nullptr.
		 */
		Frame *GetFrameAtIndex(unsigned int frame_num) const;

		/**
		 *	Crappy method, was just a quick fix. Retains data before the one Sprite object is about to release data.
		 *	Must die.
		 */
		//bool RetainData(const TextureVertex *data);

		/**
		 *	Get the name of the animation.
		 *
		 *	@return	Name of the animation.
		 */
		std::string GetAnimationName() const;
		
	private:
		Frame *head_;
		Frame *tail_;
		unsigned int t_frame_count_;
		std::string name_;
	};
	
	class SpriteAnimation : public Animation{
	public:
		SpriteAnimation(TextureVertex **vertex_data,			/*Sprite data to be rendered*/
						const SpriteAnimationData *data,			/* Animation data */
						const int repeat_count = 1,			/*Num of repeat. -1 means infinite*/
						const unsigned int final_frame_index	 = 0,	/*Frame index to be used when animation is over. Default 0*/
						const float fps = 24.0f);			/*Desired fps. Default is 24*/
		~SpriteAnimation();

		void SetRepeatCount(int c);
		void GoToFrameNumber(unsigned int frame_num);
		void SetFinalFrameIndex(unsigned int i);
		void SetFPS(float fps);
		/**
		 *	Restart animation, no mater where it is
		 */
		void Restart();
		
		/**
		 *	Get total frames in this animation.
		 *
		 *	@return	Total frame count.
		 */
		unsigned int GetFrameCount() const;

	private:
		void update(float dt);
		void next_frame();
		
		TextureVertex **vertex_data_;
		TextureVertex *final_vertex_data_;
		const SpriteAnimationData *data_;
		SpriteAnimationData::Frame *active_frame_;			// The frame executing.
		
		float clock_;					// Clock resets after each frame execution. Relevant only when using delay.
		float delay_;					// Delay between each frame.
		int repeat_count_;				// Num of repeats. -ve number will go on for a really long time.
										//	Ex: -1 will loop 4294967294 times (for a animatoin with just a single frame will run for 2+ years at 60 fps)
	};
	
}
#endif
