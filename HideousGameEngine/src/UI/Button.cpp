//
//  Button.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "Button.h"

//#include <he/Animation/AnimationUtils.h>
#include <he/UI/ImageView.h>

namespace he {
	namespace ui{

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// MARK: Button
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		Button::Button(IButtonListner *listner,
					  const Frame frame,
					   int tag) :
		View(frame),
//		animation_handle_(0UL),
//		animation_listener_(nullptr),
		listner_(listner),
		gesture_listener_(nullptr),
		tag_(tag)
		{
			// add gesture listener
			gesture_listener_ = new he::GestureListener<Button>(this, &Button::HandleGesture);
			he::g_EventLoop->AddListener(gesture_listener_);
			
			// add animation listener
			//			animation_listener_ = new he::AnimationListener<Button>(this, &Button::AnimationFinish);
		}

		Button::~Button(){
			he::g_EventLoop->RemoveListener(gesture_listener_);
			delete gesture_listener_;
			if(listner_){
				delete listner_; listner_ = nullptr;
			}
//			if(animation_listener_){
//				delete animation_listener_;
//			}
//			if(animation_handle_){
//				he::EndAnimationsWithID(he::EndAnimationFunctor::kAnimationID, animation_handle_);
//				animation_handle_ = 0UL;
//			}
		}

		void Button::self_update(float dt){
		}
		
		void Button::self_render(){
		}
		void Button::self_set_needs_display(){
			
		}
		
		void Button::HandleGesture(const he::Gesture &gesture){
			
			if(gesture.action_ == he::Gesture::kTap && gesture.state_ == he::Gesture::kEnd){
				
				//				if(gesture.state_ == he::Gesture::kBegin){
					GLKVector2 pt = gesture.GetHitPoint();
					he_Trace("\nButton[%d]\n:HandleGesture: \n%@\nFrame:%@\nPoint:%@\n",tag_,gesture,GetFrame().GetRect(),pt);

					bool hit = he::Vertex::Contains(GetFrame().GetRect(), pt);
					if(hit){
									listner_->Hit(this);
//						GLKVector2 scale_points[2] = {original_transform_.scale_, GLKVector2Multiply(original_transform_.scale_, GLKVector2Make(1.05, 1.05))};
//						he::RawAnimation<GLKVector2> *scale_up_anim = new he::RawAnimation<GLKVector2>(&transform_.scale_,
//																									   he::Tweener<GLKVector2>(he::Linear, scale_points[0], scale_points[1]),
//																									   15);
//						he::g_AnimationLoop->AddAnimation(scale_up_anim);
//						animation_handle_ = scale_up_anim->GetID();
//					}
//				}else if(animation_handle_ && gesture.state_ == he::Gesture::kEnd){
//					GLKVector2 scale_points[2] = {transform_.scale_, original_transform_.scale_};
//					he::RawAnimation<GLKVector2> *scale_down_anim = new he::RawAnimation<GLKVector2>( &transform_.scale_,
//																									 he::Tweener<GLKVector2>(he::BounceEaseOut, scale_points[0], scale_points[1]),
//																									 25);
//					scale_down_anim->SetListener(animation_listener_);
//					he::g_AnimationLoop->AddAnimation(scale_down_anim);
//					animation_handle_ = scale_down_anim->GetID();
				}
			}
		}
		

		int Button::GetTag() const{
			return tag_;
		}
//		void Button::AnimationFinish(int animation_id){
//			animation_handle_ = 0UL;
//			FILE_LOG(logDEBUG) << "Button::AnimationFinish";
//			// call action
//			listner_->Hit(this);
//		}
		
		
	} /*namespace ui*/
} /*namespace he*/

///EOF
