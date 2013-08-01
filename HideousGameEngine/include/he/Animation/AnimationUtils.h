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

	void EndAnimationsWithID(EndAnimationFunctor::IDType type, Animation::ID ID);

}

#endif
