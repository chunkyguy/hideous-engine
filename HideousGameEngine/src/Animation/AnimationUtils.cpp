//
//  AnimationUtils.cpp
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Animation/AnimationUtils.h>

#include <he/Animation/Animation.h>
#include <he/Animation/AnimationLoop.h>

namespace he {
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Helpers
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	EndAnimationFunctor::EndAnimationFunctor(IDType type, unsigned long ID) :
	id_(ID),
	type_(type)
	{}
	
	void EndAnimationFunctor::operator()(Animation *animation){
		unsigned long ID = (type_ == kAnimationID) ? animation->GetID(): animation->GetDescentID();
		if(ID == id_){
			animation->Die();
		}
	}
	
	void EndAnimationsWithID(EndAnimationFunctor::IDType type, unsigned long ID){
		g_AnimationLoop->TraverseAnimations(EndAnimationFunctor(type, ID));
	}
	
	
}