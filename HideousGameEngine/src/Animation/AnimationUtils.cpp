//
//  AnimationUtils.cpp
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Animation/AnimationUtils.h>

#include <he/Animation/AnimationLoop.h>

namespace he {
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Helpers
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	EndAnimationFunctor::EndAnimationFunctor(IDType type, Animation::ID ID) :
	id_(ID),
	type_(type)
	{}
	
	void EndAnimationFunctor::operator()(Animation *animation){
		Animation::ID ID = (type_ == kAnimationID) ? animation->GetID(): animation->GetDescentID();
		if(ID == id_){
			animation->Die();
		}
	}
	
	void EndAnimationsWithID(EndAnimationFunctor::IDType type, Animation::ID ID){
		g_AnimationLoop->TraverseAnimations(EndAnimationFunctor(type, ID));
	}
	
	
}