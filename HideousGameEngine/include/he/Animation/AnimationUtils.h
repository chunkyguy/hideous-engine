//
//  AnimationUtils.h
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_AnimationUtils_h
#define HideousGameEngine_AnimationUtils_h

namespace he {

	class Animation;
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Helpers
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	Committing suicide at destructors is such a common task, that we have a helper for it.
	//	Can be called in two ways, depending on whether it's a single animation or a animation family.
	class EndAnimationFunctor {
	public:
		typedef enum {kAnimationID, kDescentID} IDType;
		EndAnimationFunctor(IDType type, unsigned long ID);
		void operator()(he::Animation *animation);
		
	private:
		unsigned long id_;
		IDType type_;
	};

	void EndAnimationsWithID(EndAnimationFunctor::IDType type, unsigned long ID);

}

#endif
