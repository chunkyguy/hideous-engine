//
//  AnimationUtils.h
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_AnimationUtils_h
#define HideousGameEngine_AnimationUtils_h

#include <he/Animation/Animation.h>

namespace he {
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Helpers
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	Committing suicide at destructors is such a common task, that we have a helper for it.
	//	Can be called in two ways, depending on whether it's a single animation or a animation family.
	class EndAnimationFunctor {
	public:
		typedef enum {kAnimationID, kDescentID} IDType;
		EndAnimationFunctor(IDType type, Animation::ID ID);
		void operator()(Animation *animation);
		
	private:
		Animation::ID id_;
		IDType type_;
	};

	namespace animation {
		void EndAnimationsWithID(EndAnimationFunctor::IDType type, Animation::ID ID);

		/**
		 *	Get number of frames when duration and fps are available.
		 *
		 *	@param	duration Duration in seconds.
		 *	@param	fps	Frame per seconds.
		 *
		 *	@return	Number of frames
		 */
		inline unsigned int GetFramesInDuration(float duration, float fps) {
			return static_cast<unsigned int>( duration * fps );
		}
		
		/**
		 *	Get duration in seconds for some frames at some FPS
		 *
		 *	@param	frames	Number of frames.
		 *	@param	fps	Frames per seconds.
		 *
		 *	@return	duration in seconds
		 */
		inline float GetDurationForFrames(int frames, float fps) {
			return frames / fps;
		}
	}

}

#endif
