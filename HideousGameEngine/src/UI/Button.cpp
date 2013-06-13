//
//  Button.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "Button.h"

#include <he/Font/Font.h>

//namespace he {
//	namespace ui{
//
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		// MARK: Button
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Button::Button(const ButtonFactory *factory,
//					   IButtonListner *listner,
//					   int tag,
//					   const std::string &image_name,
//					   const std::string &string,
//					   he::Transform transform,
//					   GLKVector4 color) :
//		animation_handle_(0UL),
//		animation_listener_(nullptr),
//		background_(nullptr),
//		background_data_(nullptr),
//		listner_(listner),
//		gesture_listener_(nullptr),
//		original_transform_(transform),
//		transform_(transform),
//		text_(nullptr)
//		{
//			// add gesture listener
//			gesture_listener_ = new he::GestureListener<Button>(this, &Button::HandleGesture);
//			he::g_EventLoop->AddListener(gesture_listener_);
//			
//			// add animation listener
//			animation_listener_ = new he::AnimationListener<Button>(this, &Button::AnimationFinish);
//			
//			// load text
//			if(string.size()){
//				text_(new he::Text(string, transform, color))
//				factory->font.Get()->LoadText(text_);
//			}
//
//			// load background
//			GLKVector2 text_sz = text_->GetSize();
//			GLKVector2 text_eff_sz = GLKVector2MultiplyScalar(text_sz, 1.5) ;
//			background_data_ = he::CreateTextureData( factory->atlas.Get(), "button_bg.png", text_eff_sz.x, text_eff_sz.y, false);
//			background_ = new he::RenderObject( background_data_, factory->shader.Get(), factory->atlas.Get()->GetTexture(), he::g_Screen->projection_);
//		}
//
//		Button::~Button(){
//			if(background_){
//				delete background_;
//			}
//			if(background_data_){
//				delete background_data_;
//			}
//			he::g_EventLoop->RemoveListener(gesture_listener_);
//			delete gesture_listener_;
//			if(listner_){
//				delete listner_; listner_ = nullptr;
//			}
//			if(animation_listener_){
//				delete animation_listener_;
//			}
//			if(animation_handle_){
//				he::EndAnimationsWithID(he::EndAnimationFunctor::kAnimationID, animation_handle_);
//				animation_handle_ = 0UL;
//			}
//			delete text_;
//		}
//
//		void Button::update(float dt){
//			GLKVector2 text_sz = text_->GetSize();
//			background_->SetMVP(TextToNormal(transform_, text_sz).GetMVP()); 	//background_->SetMVP(transform_.GetMVP());
//			text_->SetTransform(transform_);
//			
//			
//			//	if(scale_animation_){
//			//		//		background_->SetMVP(scale_animation_transform_->GetMVP());
//			//		background_->SetMVP(TextToNormal(*scale_animation_transform_, text_->GetSize()).GetMVP());
//			//		text_->SetTransform(*scale_animation_transform_);
//			//
//			//		if(!scale_animation_->NextFrame()){
//			//			transform_ = *scale_animation_transform_;
//			//
//			//			delete scale_animation_; scale_animation_ = nullptr;
//			//			delete scale_animation_transform_; scale_animation_transform_ = nullptr;
//			//
//			//			listner_->Hit(this);
//			//		}
//			//	}
//		}
//		
//		void Button::render(){
//			background_->Render();
//			text_->Render();
//		}
//		
//		void Button::HandleGesture(const he::Gesture &gesture){
//			
//			if(gesture.action_ == he::Gesture::kTap && gesture.state_ == he::Gesture::kEnd){
//				FILE_LOG(logDEBUG) << "Button:HandleGesture: " << animation_handle_;
//				PrintGesture(gesture);
//				
//				if(!animation_handle_ && gesture.state_ == he::Gesture::kBegin){
//					GLKVector2 pt = gesture.GetHitPoint();
//					GLKVector2 sz = text_->GetSize();
//					const GLKVector2 pos = text_->GetTransform().GetPosition();
//					he::Vertex::V2 box;
//					GLKVector2 min = GLKVector2Make(pos.x, pos.y);
//					
//					he::Vertex::Set(box, pos, pos + sz );
//					bool hit = he::Vertex::Contains(box, pt);
//					if(hit){
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
//				}
//			}
//		}
//		
//		
//		void Button::AnimationFinish(int animation_id){
//			animation_handle_ = 0UL;
//			FILE_LOG(logDEBUG) << "Button::AnimationFinish";
//			// call action
//			listner_->Hit(this);
//		}
//		
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		// MARK: ButtonFactory
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		ButtonFactory::ButtonFactory( he::TextureAtlas *atls, he::TextureShader *shdr){
//			atlas.Load(atls, false);
//			shader.Load(shdr, false);
//		}
//
//		
//	} /*namespace ui*/
//} /*namespace he*/

///EOF
